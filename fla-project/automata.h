#pragma once

#include <string>

class Automata {
public:
    virtual ~Automata() = default;
    virtual void simulate(const std::string& input, bool verbose) = 0;
    virtual void printAutomata() const = 0;
    void checkInput(const std::string& input, bool verbose) const;
    void endInfo_verbose(std::string result) const;
protected:
    std::set<std::string> states;
    std::set<char> inputSymbols;
    std::string startState;
};