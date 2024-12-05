#include "pda.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stack>

void PDA::printAutomata() const {
    std::cerr << "========================================================================\n";
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
    std::cerr << "========================================================================\n";
}

void PDA::printStack(const std::stack<char>& stack) const {
    std::stack<char> tempStack = stack;
    std::vector<char> stackContents;
    while (!tempStack.empty()) {
        stackContents.push_back(tempStack.top());
        tempStack.pop();
    }

    std::cout << "Stack: ";
    for (char c : stackContents) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}