#include <iostream>

#include "CLogReader.h"

const int gBufSize = 1024;


static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)> SOURCE\n"
              << "Options:\n"
              << "\t-h,--help\t\t\t\tShow this help message\n"
              << "\t-f,--filter pattern\t\tSpecify the filter pattern"
              << std::endl;
}


int main(int argc, char* argv[]) {
    // work with args
    // - path
    // - filter
    if (argc != 4) {
        show_usage(argv[0]);
        return 1;
    }

    std::string path = "/Users/null/.gitconfig";
    std::string fltr = "lf*n";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            show_usage(argv[0]);
            return 0;
        } else if ((arg == "-f") || (arg == "--filter")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                fltr = argv[++i];
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--filter option requires one argument." << std::endl;
                return 1;
            }
        } else
            path = argv[i];

    }

    auto rdr = std::make_shared<CLogReader>();
    if(!rdr->Open(path.c_str()))
        return 1;

    rdr->SetFilter(fltr.c_str());

    char sBuf[gBufSize + 1] = {0};
    while (rdr->GetNextLine(sBuf, gBufSize)){
        std::cout << sBuf << std::endl;
        memset(sBuf, 0, sizeof(sBuf));
    }

    rdr->Close();

    return 0;
}