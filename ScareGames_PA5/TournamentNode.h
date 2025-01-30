#ifndef TOURNAMENT_NODE_H
#define TOURNAMENT_NODE_H
#include <cstddef>


template <typename T>
class TournamentTree;  

// Represents node in tourn tree
template <typename T>
class TournamentNode {
public:
    // Constructor.
    TournamentNode(T* competitor);
    // Destructor
    ~TournamentNode();

    // Getters and setters for winner child nodes
    T* getWinner() const;
    void setWinner(T* winner);

    TournamentNode<T>* getLeft() const;
    TournamentNode<T>* getRight() const;

public:
    T* winner; // Pointer to winner
    TournamentNode<T>* left; // Left child node
    TournamentNode<T>* right; // Right child node

    friend class TournamentTree<T>;
};

// Implementation of templated methods

template <typename T>
TournamentNode<T>::TournamentNode(T* competitor)
    : winner(competitor), left(nullptr), right(nullptr) {}

template <typename T>
TournamentNode<T>::~TournamentNode() {
    delete left;
    delete right;
}

template <typename T>
T* TournamentNode<T>::getWinner() const {
    return winner;
}

template <typename T>
void TournamentNode<T>::setWinner(T* winner) {
    this->winner = winner;
}

template <typename T>
TournamentNode<T>* TournamentNode<T>::getLeft() const {
    return left;
}

template <typename T>
TournamentNode<T>* TournamentNode<T>::getRight() const {
    return right;
}

#endif
