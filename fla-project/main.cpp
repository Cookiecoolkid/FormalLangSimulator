#include <iostream>
#include <string>
#include "pda.h"
#include "cli_parser.h"
#include "tm.h"

int main(int argc, char* argv[]){
    CLIParser parser(argc, argv);
    
    if (parser.automataType == CLIParser::AutomataType::PDA) {
        PDAParser pdaParser;
        PDA pda(parser.model, &pdaParser);

        // pda.printAutomata();

        pda.checkInput(parser.input, parser.verbose);
        pda.simulate(parser.input, parser.verbose);
    } else if (parser.automataType == CLIParser::AutomataType::TM) {
        TMParser tmParser;
        TM tm(parser.model, &tmParser);

        // tm.printAutomata();

        tm.checkInput(parser.input, parser.verbose);
        tm.simulate(parser.input, parser.verbose);
    }

    return 0;
}