#include "RunScareGame.h" 
#include <iostream> 
#include <string> 

int main(int argc, char* argv[]) {
    // Check commandline args
    if (argc != 4) {
        std::cout << "Error. Run again with full command line arguments." << std::endl;
        return 1; //exit
    }

    //extract commandline args
    std::string inputFile = argv[1]; //input file
    std::string outputFile = argv[2]; //output DOT file
    std::string tournamentType = argv[3]; //single or double tourn

    //is single or double elimination
    bool doubleElimination = (tournamentType == "double");

    //makes instance of runscaregame
    RunScareGame game(inputFile, outputFile, doubleElimination);
    //runs tournament
    game.runTournament();

    return 0;
}