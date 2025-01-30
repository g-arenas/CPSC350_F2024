#include "RunScareGame.h"
#include <fstream> // File handling
#include <sstream> 
#include <iostream> 

// Constructor
RunScareGame::RunScareGame(const std::string& inputFile, const std::string& outputFile, bool doubleElimination)
    : inputFile(inputFile), outputFile(outputFile), doubleElimination(doubleElimination) {}

// Main function runs tournament
void RunScareGame::runTournament() {
    loadMonsters(); // Loads competitors from input file.

    // Create tournament tree, execute game
    TournamentTree<Monster> tournament(competitors, doubleElimination);

    // elimination method
    if (doubleElimination) {
        tournament.doubleElimination();
    } else {
        tournament.singleElimination();
    }

    saveResults(tournament); // Save results to DOT file
}

// Loads from input file
void RunScareGame::loadMonsters() {
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cout << "Error opening input file: " << inputFile << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string name;
        int screamPower;

        if (ss >> name >> screamPower) {
            if (screamPower >= 0 && screamPower <= 1000) {
                competitors.push_back(new Monster(name, screamPower));
            } else {
                std::cout << "Invalid scream power level for " << name << ": " << screamPower << std::endl;
            }
        } else {
            std::cout << "Invalid line format: " << line << std::endl;
        }
    }

    file.close();
}

void RunScareGame::saveResults(TournamentTree<Monster>& tournament) {
    tournament.saveTreeAsDot(outputFile);

    for (Monster* monster : competitors) {
        delete monster;
    }
    competitors.clear();
}