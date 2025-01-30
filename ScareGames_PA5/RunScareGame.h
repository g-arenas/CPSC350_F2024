#ifndef RUN_SCARE_GAME_H
#define RUN_SCARE_GAME_H

#include "TournamentTree.h"
#include "Monster.h"
#include <vector> 
#include <string>

class RunScareGame {
public:
    // Constructor
    RunScareGame(const std::string& inputFile, const std::string& outputFile, bool doubleElimination);
    // Executes tourn
    void runTournament();

private:
    std::string inputFile;  
    std::string outputFile; 
    bool doubleElimination; 
    std::vector<Monster*> competitors; 

    void loadMonsters();

    void saveResults(TournamentTree<Monster>& tournament);
};

#endif
