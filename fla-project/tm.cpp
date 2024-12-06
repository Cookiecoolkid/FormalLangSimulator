#include "tm.h"
#include <iostream>
#include <algorithm>
#include <stack>
#include <cassert>

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

    tapes.resize(numTapes, std::deque<char>(1, blankSymbol));
    heads.resize(numTapes);
    initial_heads.resize(numTapes);
    for (int i = 0; i < numTapes; ++i) {
        heads[i] = tapes[i].begin();
        initial_heads[i] = heads[i];
    }
}

void TM::moveLeft(int index) {
    assert(0 <= index && index < numTapes);
    std::deque<char>& tape = tapes[index];
    std::deque<char>::iterator& head = heads[index];

    if (head == tape.begin()) {
        tape.push_front(blankSymbol);
        head = tape.begin();
    } else {
        --head;
    }
}

void TM::moveRight(int index) {
    assert(0 <= index && index < numTapes);
    std::deque<char>& tape = tapes[index];
    std::deque<char>::iterator& head = heads[index];

    ++head;
    if (head == tape.end()) {
        tape.push_back(blankSymbol);
        head = tape.end() - 1;
    }
}

bool TM::matches(const std::string& inputSymbols, const std::string& pattern) const{
    if (inputSymbols.size() != pattern.size()) {
        return false;
    }
    for (size_t i = 0; i < inputSymbols.size(); ++i) {
        if ((pattern[i] != '*' && pattern[i] != inputSymbols[i]) || 
            (pattern[i] == '*' && inputSymbols[i] == blankSymbol)) {
            return false;
        }
    }
    return true;
}

void TM::simulate(const std::string& input, bool verbose) {

    std::string currentState = startState;
    int step = 0;

    // 将输入写入第一个磁带
    tapes[0].clear();
    for (char ch : input) {
        tapes[0].push_back(ch);
    }
    tapes[0].push_back(blankSymbol); // 在输入的末尾添加一个空字符
    heads[0] = tapes[0].begin(); // 将头指针指向第一个磁带的开头
    initial_heads[0] = heads[0];

    while (true) {

        if (verbose) {
            stepInfo_verbose(step++, currentState);
        }

        std::string inputSymbols;
        for (int i = 0; i < numTapes; ++i) {
            inputSymbols.push_back(heads[i] != tapes[i].end() ? *heads[i] : blankSymbol);
        }

        auto keyMatched = std::make_tuple(currentState, inputSymbols);
        auto transition = transitionFunctions.find(keyMatched);

        if (transition == transitionFunctions.end()) {
            // 尝试通配符匹配
            for (const auto& kv : transitionFunctions) {
                const auto& key = kv.first;
                const std::string& state = std::get<0>(key);
                const std::string& pattern = std::get<1>(key);
                if (state == currentState && matches(inputSymbols, pattern)) {
                    keyMatched = key;
                    transition = transitionFunctions.find(key);
                    break;
                }
            }
        }

        if (transition == transitionFunctions.end()) {
            break;
        }

        // 转移之后的处理逻辑
        std::string patternMatched = std::get<1>(keyMatched);
        std::string writeSymbols, directions, nextState;

        std::tie(writeSymbols, directions, nextState) = transition->second;
        currentState = nextState;

        for (int i = 0; i < numTapes; ++i) {
            if (patternMatched[i] != '*' || (patternMatched[i] == '*' && writeSymbols[i] != '*')) 
                *heads[i] = writeSymbols[i];
            
            if (directions[i] == 'l') moveLeft(i);
            else if (directions[i] == 'r') moveRight(i);
            else if (directions[i] == '*') ; // stay
        }
    }

    std::deque<char>& tape = tapes[0];
    std::deque<char>::iterator start = tape.begin();
    std::string result;

    while (start != tape.end() && *start == blankSymbol) {
        ++start;
    }

    std::deque<char>::iterator finish = tape.end();
    while (finish != start && *(finish - 1) == blankSymbol) {
        --finish;
    }

    for (auto it = start; it != finish; ++it) {
        result.push_back(*it);
    }

    if (verbose) endInfo_verbose(result);
    else std::cout << result << std::endl;
}

