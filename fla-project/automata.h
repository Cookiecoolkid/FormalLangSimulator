#pragma once

#include <string>

class Automata {
public:
    virtual ~Automata() = default;
    virtual void printAutomata() const = 0;
};