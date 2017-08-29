//
// Created by null on 28.08.17.
//

#include "CLogReader.h"

#include <iostream>

bool CLogReader::Open(const char* aPath){

    mStream.open(aPath, std::ifstream::in);
    if(mStream.fail())
    {
        std::cerr << "Unable to open file " << aPath << std::endl;
        return false;
    }
    return true;
}

void CLogReader::Close(){
    mStream.close();
}

bool CLogReader::SetFilter(const char* aFilter){
    // replace
    // order*closed => (order)(.*)(closed)
    //
    // add slashes before special chars
    // [ { ( ) } ] . \ / ^

    bool isChar = false;
    std::string out;
    std::string src(aFilter);

    for(auto i = 0; i < src.length(); i++){
        switch (src.at(i)){
            case '[':
            case ']':
            case '(':
            case ')':
            case '{':
            case '}':
            case ':':
            case '.':
            case '/':
            case '\\':
                if (!isChar)
                    out += '(';

                out += '\\';
                out += src.at(i);
                isChar = true;
                break;

            case '*':
            case '?':
                if (isChar)
                    out += ')';
                out += '(';
                out += '.';
                out += src.at(i);
                out += ')';
                isChar = false;

                break;
            default:
                if (!isChar)
                    out += '(';
                out += src.at(i);
                isChar = true;
                break;
        }
    }
    if(isChar)
        out += ')';

    //std::cout << aFilter << " : " << out << std::endl;

    mFilter.assign(out, std::regex::ECMAScript);
    return true;
}

bool CLogReader::GetNextLine(char* aBuf, const int aSize){
    if(!mStream.is_open() || mStream.fail())
        return false;

    std::string line;
    bool result;
    do {
        std::getline(mStream, line);
        if (mStream.fail())
            return false;

        std::smatch what;
        result = std::regex_search(line, what, mFilter);
        if (result) {
            auto rest = line.length() - what.position();
            if(aSize < rest)
                rest = aSize;

            memcpy(aBuf, line.substr(what.position(), rest).c_str(), rest);
        }

    }
    while (!result);

    return true;
}