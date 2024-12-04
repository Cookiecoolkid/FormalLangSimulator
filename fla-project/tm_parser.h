#pragma once

#include "parser.h"
#include <string>

class TMParser : public Parser {
public:
    void parse(const std::string& filename) override;
};