#include "tm.h"
#include <iostream>
#include <algorithm>

TM::TM(const std::string& filename, TMParser* parser) : parser(parser) {
    parser->parse(filename);
    states = parser->states;
    inputSymbols = parser->inputSymbols;
    tapeSymbols = parser->tapeSymbols;
    startState = parser->startState;
    blankSymbol = parser->blankSymbol;
    acceptStates = parser->acceptStates;
    numTapes = parser->numTapes;
    transitionFunctions = parser->transitionFunctions;

    tapes.resize(numTapes);
    heads.resize(numTapes, 0);
}

void TM::simulate(const std::string& input, bool verbose) const {

}

void TM::checkInput(const std::string& input) const {
    for (char ch : input) {
        if (inputSymbols.find(ch) == inputSymbols.end()) {
            std::cerr << "Invalid input symbol: " << ch << std::endl;
            exit(1);
        }
    }
}

void TM::printAutomata() const {
    std::cerr << "========================================================================\n";
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
    std::cerr << "========================================================================\n";
}

void TM::printTapes() const {
    for (int i = 0; i < numTapes; ++i) {
        std::cerr << "Tape " << i + 1 << ": ";
        for (char ch : tapes[i]) {
            std::cerr << ch;
        }
        std::cerr << " (Head at position " << heads[i] << ")\n";
    }
}