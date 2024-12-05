#include <iostream>
#include <string>
#include "pda.h"
#include "cli_parser.h"

int main(int argc, char* argv[]){
    CLIParser parser(argc, argv);
    
    if (parser.automataType == CLIParser::AutomataType::PDA) {
        PDAParser pdaParser;
        PDA pda(parser.model, &pdaParser);
        pda.checkInput(parser.input);

        pda.printAutomata();

        pda.simulate(parser.input, parser.verbose);
    } else if (parser.automataType == CLIParser::AutomataType::TM) {
        // TODO
    }

    return 0;
}