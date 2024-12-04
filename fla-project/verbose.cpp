#include "pda.h"
#include <fstream>
#include <iostream>

void PDA::printAutomata() const {
    std::cout << "States: ";
    for (const auto& state : states) {
        std::cout << state << " ";
    }
    std::cout << "\nInput Symbols: ";
    for (const auto& symbol : inputSymbols) {
        std::cout << symbol << " ";
    }
    std::cout << "\nStack Symbols: ";
    for (const auto& symbol : stackSymbols) {
        std::cout << symbol << " ";
    }
    std::cout << "\nStart State: " << startState;
    std::cout << "\nStart Stack Symbol: " << startStackSymbol;
    std::cout << "\nAccept States: ";
    for (const auto& state : acceptStates) {
        std::cout << state << " ";
    }
    std::cout << "\nTransition Functions:\n";
    for (const auto& kv : transitionFunctions) {
        const auto& key = kv.first;
        const auto& value = kv.second;
        std::string currentState;
        char inputSymbol, stackSymbol;
        std::tie(currentState, inputSymbol, stackSymbol) = key;
        std::string nextState, stackPush;
        std::tie(nextState, stackPush) = value;
        std::cout << currentState << " " << inputSymbol << " " << stackSymbol << " -> " << nextState << " " << stackPush << "\n";
    }
}