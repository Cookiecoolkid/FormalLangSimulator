#include "tm_parser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

void TMParser::parse(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // 去除行首的空格
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));

        if (line.empty() || line[0] == ';') continue;

        if (line[0] == '#') {
            size_t pos = line.find(" = ");
            if (pos == std::string::npos) {
                std::cerr << "syntax error: missing ' = ' in line: " << line << std::endl;
                exit(1);
            }
            std::string key = line.substr(0, pos);
            std::string value = trim(line.substr(pos + 3));

            if ((key != "#q0" && key != "#B" && key != "#N") && (value.front() != '{' || value.back() != '}')) {
                std::cerr << "syntax error: missing '{' or '}' in line: " << line << std::endl;
                exit(1);
            }

            if (key == "#Q") {
                std::vector<std::string> statesVec = split(value.substr(1, value.size() - 2), ',');
                states.insert(statesVec.begin(), statesVec.end());
            } else if (key == "#S") {
                std::vector<std::string> symbolsVec = split(value.substr(1, value.size() - 2), ',');
                for (const auto& symbol : symbolsVec) {
                    if (symbol.size() != 1) {
                        std::cerr << "syntax error: invalid input symbol in line: " << line << std::endl;
                        exit(1);
                    }
                    inputSymbols.insert(symbol[0]);
                }
            } else if (key == "#G") {
                std::vector<std::string> symbolsVec = split(value.substr(1, value.size() - 2), ',');
                for (const auto& symbol : symbolsVec) {
                    if (symbol.size() != 1) {
                        std::cerr << "syntax error: invalid tape symbol in line: " << line << std::endl;
                        exit(1);
                    }
                    tapeSymbols.insert(symbol[0]);
                }
            } else if (key == "#q0") {
                startState = value;
            } else if (key == "#B") {
                if (value.size() != 1) {
                    std::cerr << "syntax error: invalid blank symbol in line: " << line << std::endl;
                    exit(1);
                }
                blankSymbol = value[0];
            } else if (key == "#F") {
                std::vector<std::string> statesVec = split(value.substr(1, value.size() - 2), ',');
                acceptStates.insert(statesVec.begin(), statesVec.end());
            } else if (key == "#N") {
                try {
                    numTapes = std::stoi(value);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "syntax error: invalid number of tapes in line: " << line << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << "syntax error: unknown key in line: " << line << std::endl;
                exit(1);
            }
        } else {
            std::istringstream iss(line);
            std::string currentState, readSymbols, writeSymbols, directions, nextState;
            if (!(iss >> currentState >> readSymbols >> writeSymbols >> directions >> nextState)) {
                std::cerr << "syntax error: invalid transition function in line: " << line << std::endl;
                exit(1);
            }
            transitionFunctions[{currentState, readSymbols}] = {writeSymbols, directions, nextState};
        }
    }
}