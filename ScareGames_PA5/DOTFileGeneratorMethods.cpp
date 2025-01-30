#include <fstream>
#include <iostream> // Provides input-output operations.
#include "TournamentNode.h" // Defines TournamentNode, used for the tournament tree structure.

// Function to save tree as DOT file
template <typename T>
void saveTreeAsDot(const std::string& filename, TournamentNode<T>* rootNode) {
    //open file for writing 
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filename << "\n";
        return;
    }

    //write DOT & save nodes
    file << "digraph TournamentTree {\n";
    int nodeID = 0;
    saveTreeAsDotHelper(rootNode, file, nodeID);
    file << "}\n";
    file.close();
}

// helper function for DOT file generation - writes nodes & edges
template <typename T>
void saveTreeAsDotHelper(TournamentNode<T>* node, std::ofstream& file, int& nodeID) {
    if (node == nullptr) return;

    
    int currentID = nodeID++;
    file << "    node" << currentID << " [label=\"" << node->getWinner()->getName()
         << " (Power: " << node->getWinner()->getscreamPower() << ")\"];\n";

    //process L & R children if avail
    if (node->getLeft()) {
        int leftID = nodeID;
        saveTreeAsDotHelper(node->getLeft(), file, nodeID);
        file << "    node" << currentID << " -> node" << leftID << ";\n";
    }

    if (node->getRight()) {
        int rightID = nodeID;
        saveTreeAsDotHelper(node->getRight(), file, nodeID);
        file << "    node" << currentID << " -> node" << rightID << ";\n";
    }
}
