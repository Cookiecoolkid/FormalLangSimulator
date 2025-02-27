#include "pda_parser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream> 

void PDAParser::parse(const std::string& filename) {
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
                std::cerr << "syntax error" << std::endl;
                exit(1);
            }
            std::string key = line.substr(0, pos);
            std::string value = trim(line.substr(pos + 3));

            if ((key != "#q0" && key != "#z0") && (value.front() != '{' || value.back() != '}')) {
                std::cerr << "syntax error" << std::endl;
                exit(1);
            }

            if (key == "#Q") {
                std::vector<std::string> statesVec = split(value.substr(1, value.size() - 2), ',');
                states.insert(statesVec.begin(), statesVec.end());
            } else if (key == "#S") {
                std::vector<std::string> symbolsVec = split(value.substr(1, value.size() - 2), ',');
                for (const auto& symbol : symbolsVec) {
                    if (symbol.size() != 1) {
                        std::cerr << "syntax error" << std::endl;
                        exit(1);
                    }
                    inputSymbols.insert(symbol[0]);
                }
            } else if (key == "#G") {
                std::vector<std::string> symbolsVec = split(value.substr(1, value.size() - 2), ',');
                for (const auto& symbol : symbolsVec) {
                    if (symbol.size() != 1) {
                        std::cerr << "syntax error" << std::endl;
                        exit(1);
                    }
                    stackSymbols.insert(symbol[0]);
                }
            } else if (key == "#q0") {
                startState = value;
            } else if (key == "#z0") {
                if (value.size() != 1) {
                    std::cerr << "syntax error" << std::endl;
                    exit(1);
                }
                startStackSymbol = value[0];
            } else if (key == "#F") {
                std::vector<std::string> statesVec = split(value.substr(1, value.size() - 2), ',');
                acceptStates.insert(statesVec.begin(), statesVec.end());
            } else {
                std::cerr << "syntax error" << std::endl;
                exit(1);
            }
        } else {
            std::istringstream iss(line);
            std::string currentState, nextState, stackPush;
            char inputSymbol, stackSymbol;
            if (!(iss >> currentState >> inputSymbol >> stackSymbol >> nextState >> stackPush)) {
                std::cerr << "syntax error" << std::endl;
                exit(1);
            }

            if (states.find(currentState) == states.end() || 
                states.find(nextState) == states.end()) {
                std::cerr << "syntax error" << std::endl;
                exit(1);
            }

            if (inputSymbol != '_' && inputSymbols.find(inputSymbol) == inputSymbols.end()) {
                std::cerr << "syntax error" << std::endl;
                exit(1);
            }

            if (stackSymbol != '_' && stackSymbols.find(stackSymbol) == stackSymbols.end()) {
                std::cerr << "syntax error" << std::endl;
                exit(1);
            }

            for (const auto& symbol : stackPush) {
                if (symbol != '_' && symbol != '_' && stackSymbols.find(symbol) == stackSymbols.end()) {
                    std::cerr << "syntax error" << std::endl;
                    exit(1);
                }
            }

            transitionFunctions[{currentState, inputSymbol, stackSymbol}] = {nextState, stackPush};
        }
    }
}