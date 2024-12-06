#pragma once

#include <string>
#include <set>
#include <map>
#include <tuple>
#include <vector>
#include <deque>
#include "automata.h"
#include "tm_parser.h"

class TM : public Automata {
public:
    TM(const std::string& filename, TMParser* parser);
    void moveLeft(int index);
    void moveRight(int index);
    bool matches(const std::string& inputSymbols, const std::string& pattern) const;
    void simulate(const std::string& input, bool verbose) override;
    void printAutomata() const override;

    void stepInfo_verbose(int step, const std::string& currentState) const;
private:
    std::set<char> tapeSymbols;
    char blankSymbol;
    std::set<std::string> acceptStates;
    int numTapes;
    std::map<std::tuple<std::string, std::string>, std::tuple<std::string, std::string, std::string>> transitionFunctions;
    TMParser* parser;

    mutable std::vector<std::deque<char>> tapes;
    mutable std::vector<std::deque<char>::iterator> heads;
    std::vector<std::deque<char>::iterator> initial_heads;
};