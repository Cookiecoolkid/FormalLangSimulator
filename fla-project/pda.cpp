#include "pda.h"
#include <iostream>
#include <algorithm>
#include <stack>

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

/*
** PDA::simulate 函数
** 仅通过状态机到达接受状态时且消耗完 input 才接受 
*/

void PDA::simulate(const std::string& input, bool verbose) const {
    std::string currentState = startState;
    std::stack<char> stack;
    stack.push(startStackSymbol);

    size_t inputIndex = 0;
    while (true) {
        char inputSymbol = (inputIndex < input.size()) ? input[inputIndex] : '_';
        char stackTop = stack.empty() ? '_' : stack.top();

        auto transition = transitionFunctions.find(std::make_tuple(currentState, inputSymbol, stackTop));
        
        // 中间不允许穿插空转移
        // if (transition == transitionFunctions.end()) {
        //     transition = transitionFunctions.find(std::make_tuple(currentState, '_', stackTop));
        // }

        if (verbose) {
            std::cerr << "Current State: " << currentState << std::endl;
            std::cerr << "Read Symbol: " << inputSymbol << std::endl;
            printStack(stack);
        }

        if (transition == transitionFunctions.end()) {
            break;
        }

        std::string nextState;
        std::string stackPush;
        std::tie(nextState, stackPush) = transition->second;
        currentState = nextState;

        if (!stack.empty()) {
            stack.pop();
        }
        
        for (auto it = stackPush.rbegin(); it != stackPush.rend(); ++it) {
            if (*it != '_') {
                stack.push(*it);
            }
        }

        if (inputSymbol != '_') {
            ++inputIndex;
        }
    }

    if (acceptStates.find(currentState) != acceptStates.end() && inputIndex >= input.size()) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
}