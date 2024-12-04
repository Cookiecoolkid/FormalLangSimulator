#pragma once

#include <string>
#include <vector>

class Parser {
public:
    virtual ~Parser() = default;
    virtual void parse(const std::string& filename) = 0;

protected:
    std::string trim(const std::string& str);
    std::vector<std::string> split(const std::string& str, char delimiter);
};