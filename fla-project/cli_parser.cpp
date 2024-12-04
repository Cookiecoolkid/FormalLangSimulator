#include "cli_parser.h"
#include "pda_parser.h"
#include "tm_parser.h"
#include <iostream>
#include <sstream>

CLIParser::CLIParser(int argc, char* argv[]) {
    parseArguments(argc, argv);
}

CLIParser::~CLIParser() {

}

void CLIParser::parseArguments(int argc, char* argv[]) {
    verbose = false;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help" || argc < 3) {
            // 显示帮助信息
            std::cerr << "usage:    fla [-h|--help] <pda|tm> <input>\n";
            std::cerr << "          fla [-v|--verbose] [-h|--help] <tm> <input>\n";
            exit(0);
        } else if (arg == "-v" || arg == "--verbose") {
            verbose = true;
        } else if (automataType != AutomataType::EMPTY) {
            input = arg;
        } else {
            model = arg;
            size_t pos = arg.find_last_of('.');
            if (pos == std::string::npos) {
                std::cerr << "Invalid file format" << std::endl;
                exit(1);
            }
            std::string suffix = arg.substr(pos + 1);
            if (suffix == "pda") {
                automataType = AutomataType::PDA;
            } else if (suffix == "tm") {
                automataType = AutomataType::TM;
            } else {
                std::cerr << "Invalid file format" << std::endl;
                exit(1);
            }
        }
    }
}

void CLIParser::parse(const std::string& filename) {
    // do nothing
}