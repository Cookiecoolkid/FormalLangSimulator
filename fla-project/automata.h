#pragma once

#include <string>

class Automata {
public:
    virtual ~Automata() = default;
    virtual void simulate(const std::string& input, bool verbose) const = 0;
    virtual void checkInput(const std::string& input) const = 0;
    virtual void printAutomata() const = 0;
};