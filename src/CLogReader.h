//
// Created by null on 28.08.17.
//

#ifndef METAQUOTES_CLOGREADER_H
#define METAQUOTES_CLOGREADER_H


#include "ILogReader.h"

#include <fstream>
#include <regex>

class CLogReader : public ILogReader {
public:
    explicit CLogReader() = default;
    ~CLogReader() = default;

    CLogReader& operator=(const CLogReader&) = delete; // disallow use of assignment operator
    CLogReader(const CLogReader&) = delete; // disallow copy construction

    CLogReader(CLogReader&&) = delete; // disallow move construction


    bool Open(const char*) final;
    void Close() final;

    bool SetFilter(const char*) final;
    bool GetNextLine(char*, const int) final;

private:
    std::regex mFilter;
    std::ifstream mStream;
};


#endif //METAQUOTES_CLOGREADER_H
