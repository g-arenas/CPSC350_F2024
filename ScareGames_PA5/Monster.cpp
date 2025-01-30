#include "Monster.h"

// Constructor - name and scream power
// Initializes a Monster with a name and scream power level.
Monster::Monster(std::string name, int screamPower)
    : name(name), screamPower(screamPower) {}

// Getters - return the monster name
std::string Monster::getName() const {
    return name;
}

//return monster scream power
int Monster::getscreamPower() const {
    return screamPower;
}

//checks monster a < monster 2 scream power
bool Monster::isLess(const Monster& a, const Monster& b) {
    return a.screamPower < b.screamPower;
}

//checks monster a is > monster 2 scream power
bool Monster::isGreater(const Monster& a, const Monster& b) {
    return a.screamPower > b.screamPower;
}

//checks monster a = monster 2 scream power
bool Monster::isEqual(const Monster& a, const Monster& b) {
    return a.screamPower == b.screamPower;
}
