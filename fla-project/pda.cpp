#include "pda.h"

PDA::PDA(const std::string& filename, PDAParser* parser) : parser(parser) {
    parser->parse(filename);
    states = parser->states;
    inputSymbols = parser->inputSymbols;
    stackSymbols = parser->stackSymbols;
    startState = parser->startState;
    startStackSymbol = parser->startStackSymbol;
    acceptStates = parser->acceptStates;
    transitionFunctions = parser->transitionFunctions;
}