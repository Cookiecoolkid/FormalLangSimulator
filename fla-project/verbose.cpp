#include "pda.h"
#include "tm.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stack>
#include <iomanip>

void Automata::checkInput(const std::string& input, bool verbose) const {
    if (verbose) {
        std::cerr << "Input: " << input << std::endl;
    }

    for (char c : input) {
        if (inputSymbols.find(c) == inputSymbols.end()) {
            if (!verbose) {
                std::cerr << "illegal input" << std::endl;
                exit(1);
            } else {
                std::cerr << "==================== ERR ====================" << std::endl;
                std::cerr << "error: '" << c << "' was not declared in the set of input symbols" << std::endl;
                std::cerr << "Input: " << input << std::endl;

                std::string::size_type pos = input.find(c);
                std::cerr << "       ";
                for (int i = 0; i < pos; ++i) {
                    std::cerr << " ";
                }
                std::cerr << "^" << std::endl;
                std::cerr << "==================== END ====================" << std::endl;
                exit(1);
            }
        }
    }

    std::cerr << "==================== RUN ====================" << std::endl;
}

void Automata::endInfo_verbose(std::string result) const {
    std::cerr << "Result: " << result << std::endl;
    std::cerr << "==================== END ====================";
    std::cerr << std::endl;
}

void PDA::stepInfo_verbose(int step, const std::string& currentState, const char& inputSymbol) const {
    std::cerr << "Step  : " << step << std::endl;
    std::cerr << "State : " << currentState << std::endl;
    std::cerr << "Read  : " << inputSymbol << std::endl;
    std::cerr << "Stack : ";

    std::stack<char> tempStack = stack;
    while (!tempStack.empty()) {
        std::cerr << tempStack.top() << " ";
        tempStack.pop();
    }

    std::cerr << std::endl;

    std::cerr << "---------------------------------------------" << std::endl;
}

void TM::stepInfo_verbose(int step, const std::string& currentState) const {
    std::cerr << "Step   : " << step << std::endl;
    std::cerr << "State  : " << currentState << std::endl;

    for (int i = 0; i < numTapes; ++i) {
        std::deque<char>& tape = tapes[i];
        auto head = heads[i];

        // 找到最左和最右的非空字符的位置，若碰到头指针提前结束
        auto left = tape.begin();
        while (left != tape.end() && left != head && *left == blankSymbol) ++left;
        
        auto right = tape.end() - 1;
        while (right != left && right != head && *right == blankSymbol) --right;

        // 计算索引范围
        int leftIndex = std::distance(initial_heads[i], left);
        int rightIndex = std::distance(initial_heads[i], right);

        // 打印索引
        std::cerr << "Index" << i << " : ";
        std::vector<int> indexWidths;
        for (int j = leftIndex; j <= rightIndex; ++j) {
            int indexWidth = std::to_string(j >= 0 ? j : -j).size();
            indexWidths.push_back(indexWidth);
            std::cerr << std::setw(indexWidth) << std::left << (j >= 0 ? j : -j) << " ";
        }
        std::cerr << std::endl;

        // 打印磁带内容
        std::cerr << "Tape" << i << "  : ";
        auto it = left;
        for (size_t k = 0; k < indexWidths.size(); ++k) {
            std::cerr << std::setw(indexWidths[k]) << std::left << *it << " ";
            ++it;
        }
        std::cerr << std::endl;

        // 打印头指针位置
        std::cerr << "Head" << i << "  : ";
        for (size_t k = 0; k < indexWidths.size(); ++k) {
            int currentIndex = leftIndex + k;
            if (std::distance(initial_heads[i], head) == currentIndex) {
                std::cerr << std::setw(indexWidths[k]) << std::left << "^" << " ";
            } else {
                std::cerr << std::setw(indexWidths[k]) << std::left << " " << " ";
            }
        }
        std::cerr << std::endl;
    }

    std::cerr << "---------------------------------------------" << std::endl;
}

void PDA::printAutomata() const {
    std::cerr << "---------------------------------------------\n";
    std::cerr << "States: ";
    for (const auto& state : states) {
        std::cerr << state << " ";
    }
    std::cerr << "\nInput Symbols: ";
    for (const auto& symbol : inputSymbols) {
        std::cerr << symbol << " ";
    }
    std::cerr << "\nStack Symbols: ";
    for (const auto& symbol : stackSymbols) {
        std::cerr << symbol << " ";
    }
    std::cerr << "\nStart State: " << startState;
    std::cerr << "\nStart Stack Symbol: " << startStackSymbol;
    std::cerr << "\nAccept States: ";
    for (const auto& state : acceptStates) {
        std::cerr << state << " ";
    }
    std::cerr << "\nTransition Functions:\n";
    for (const auto& kv : transitionFunctions) {
        const auto& key = kv.first;
        const auto& value = kv.second;
        std::string currentState;
        char inputSymbol, stackSymbol;
        std::tie(currentState, inputSymbol, stackSymbol) = key;
        std::string nextState, stackPush;
        std::tie(nextState, stackPush) = value;
        std::cerr << currentState << " " << inputSymbol << " " << stackSymbol << " -> " << nextState << " " << stackPush << "\n";
    }
    std::cerr << "---------------------------------------------\n";
}

void TM::printAutomata() const {
    std::cerr << "---------------------------------------------\n";
    std::cerr << "States: ";
    for (const auto& state : states) {
        std::cerr << state << " ";
    }
    std::cerr << "\nInput Symbols: ";
    for (const auto& symbol : inputSymbols) {
        std::cerr << symbol << " ";
    }
    std::cerr << "\nTape Symbols: ";
    for (const auto& symbol : tapeSymbols) {
        std::cerr << symbol << " ";
    }
    std::cerr << "\nStart State: " << startState;
    std::cerr << "\nBlank Symbol: " << blankSymbol;
    std::cerr << "\nAccept States: ";
    for (const auto& state : acceptStates) {
        std::cerr << state << " ";
    }
    std::cerr << "\nNumber of Tapes: " << numTapes;
    std::cerr << "\nTransition Functions:\n";
    for (const auto& kv : transitionFunctions) {
        const auto& key = kv.first;
        const auto& value = kv.second;
        std::string currentState, readSymbols;
        std::tie(currentState, readSymbols) = key;
        std::string writeSymbols, directions, nextState;
        std::tie(writeSymbols, directions, nextState) = value;
        std::cerr << currentState << " " << readSymbols << " -> " << writeSymbols << " " << directions << " " << nextState << "\n";
    }
    std::cerr << "---------------------------------------------\n";
}

