#ifndef TOURNAMENT_TREE_H
#define TOURNAMENT_TREE_H

#include "TournamentNode.h" //Tree structure.
#include <vector> 
#include <string> 
#include <fstream> 
#include <iostream> 
#include "DOTFileGeneratorMethods.cpp" 

template <typename T>
class TournamentTree {
public:
//constructor
    TournamentTree(std::vector<T*>& competitors, bool doubleElimination = false);
    // Destructor
    ~TournamentTree();

    //single elimination tourn
    void singleElimination();
    //double elimination tourn
    void doubleElimination();
    // saves to dot
    void saveTreeAsDot(const std::string& filename);

private:
    TournamentNode<T>* root; // Root node tourn tree.
    std::vector<T*> competitors; 
    bool isDoubleElimination; 

    // tree for single elimination tourn
    void buildSingleEliminationTree();
    // tree for double elimination tourn
    void buildDoubleEliminationTree();
//moves to next round
    void advanceNext(std::vector<TournamentNode<T>*>& currentRound);
    // winner
    TournamentNode<T>* simulateMatch(TournamentNode<T>* node1, TournamentNode<T>* node2);
    //deletes all nodes from given node
    void deleteTree(TournamentNode<T>* node);
};

//constructor
template <typename T>
TournamentTree<T>::TournamentTree(std::vector<T*>& competitors, bool doubleElimination)
    : competitors(competitors), isDoubleElimination(doubleElimination), root(nullptr) {
    //builds tree based off elimination
    if (doubleElimination) {
        buildDoubleEliminationTree();
    } else {
        buildSingleEliminationTree();
    }
}

// Destructor
template <typename T>
TournamentTree<T>::~TournamentTree() {
    deleteTree(root);
}

//deletes all nodes in tree
template <typename T>
void TournamentTree<T>::deleteTree(TournamentNode<T>* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

//runs single elimination tourn
template <typename T>
void TournamentTree<T>::singleElimination() {
    std::vector<TournamentNode<T>*> currentRound;
    // Initialize 1st round with competitors
    for (auto* competitor : competitors) {
        currentRound.push_back(new TournamentNode<T>(competitor));
    }

    // Continue until theres a champion
    while (currentRound.size() > 1) {
        advanceNext(currentRound);
    }

    root = currentRound[0]; // Set final champion as root node
}

// Runs double elimination tournament by handling both main and losers' brackets.
template <typename T>
void TournamentTree<T>::doubleElimination() {
    buildDoubleEliminationTree(); // Builds the initial double-elimination structure.

    TournamentNode<T>* mainBracketChampion = root->left; // Main bracket champion
    TournamentNode<T>* losersBracketChampion = root->right; // Loser bracket champion

    // If main and losers' bracket champions are differen - final match
    if (losersBracketChampion->getWinner() != mainBracketChampion->getWinner()) {
        root = simulateMatch(mainBracketChampion, losersBracketChampion);
    }
}

// Saves as dot
template <typename T>
void TournamentTree<T>::saveTreeAsDot(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file for DOT output: " << filename << "\n";
        return;
    }

    file << "digraph TournamentTree {\n";
    int nodeID = 0;
    saveTreeAsDotHelper(root, file, nodeID); // Calls the helper function to traverse the tree.
    file << "}\n";
    file.close();
}

// Builds tree for single-elim tourn
template <typename T>
void TournamentTree<T>::buildSingleEliminationTree() {
    std::vector<TournamentNode<T>*> currentRound;
    // Initialize 1st round with all competitors
    for (auto* competitor : competitors) {
        currentRound.push_back(new TournamentNode<T>(competitor));
    }

    // Continue until theres a champion
    while (currentRound.size() > 1) {
        advanceNext(currentRound);
    }

    root = currentRound[0]; 
}

// Builds tree for double elim tourn
template <typename T>
void TournamentTree<T>::buildDoubleEliminationTree() {
    std::vector<TournamentNode<T>*> mainBracket; // Main bracket for winners
    std::vector<TournamentNode<T>*> losersBracket; // Losers bracket for eliminated competitors

    // Initialize main bracket with all competitors
    for (auto* competitor : competitors) {
        mainBracket.push_back(new TournamentNode<T>(competitor));
    }

    // Process rounds in main bracket, movlosers to L bracket
    while (mainBracket.size() > 1) {
        std::vector<TournamentNode<T>*> nextMainRound;

        for (size_t i = 0; i < mainBracket.size(); i += 2) {
            if (i + 1 < mainBracket.size()) {
                TournamentNode<T>* matchNode = simulateMatch(mainBracket[i], mainBracket[i + 1]);
                nextMainRound.push_back(matchNode);

                TournamentNode<T>* loserNode = (matchNode->getWinner() == mainBracket[i]->getWinner())
                                               ? mainBracket[i + 1]
                                               : mainBracket[i];
                losersBracket.push_back(loserNode);
            } else {
                nextMainRound.push_back(mainBracket[i]);
            }
        }
        mainBracket = nextMainRound;
    }

    TournamentNode<T>* mainChampionNode = mainBracket[0];

    while (losersBracket.size() > 1) {
        advanceNext(losersBracket);
    }

    //Last remaining node in loser bracket becomes loser bracket champion
    TournamentNode<T>* losersChampionNode = losersBracket[0];

    // Final match between main and loser bracket champions
    root = new TournamentNode<T>(nullptr); //stores final winner
    root->left = mainChampionNode;
    root->right = losersChampionNode;
}

template <typename T>
void TournamentTree<T>::advanceNext(std::vector<TournamentNode<T>*>& currentRound) {
    std::vector<TournamentNode<T>*> nextRound;

    // Pair competitors for matches
    for (size_t i = 0; i < currentRound.size(); i += 2) {
        if (i + 1 < currentRound.size()) {
            TournamentNode<T>* matchNode = simulateMatch(currentRound[i], currentRound[i + 1]);
            nextRound.push_back(matchNode);
        } else {
            nextRound.push_back(currentRound[i]);
        }
    }

    currentRound = nextRound;
}

template <typename T>
TournamentNode<T>* TournamentTree<T>::simulateMatch(TournamentNode<T>* node1, TournamentNode<T>* node2) {
    T* winner = (T::isGreater(*node1->getWinner(), *node2->getWinner())) ? node1->getWinner() : node2->getWinner();
    
    TournamentNode<T>* matchNode = new TournamentNode<T>(winner);
    matchNode->left = node1;
    matchNode->right = node2;
    matchNode->setWinner(winner);

    return matchNode;
}

#endif