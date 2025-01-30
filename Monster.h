#ifndef MONSTER_H
#define MONSTER_H

#include <string> 

class Monster {
    public:
        // Constructor - name and power lvl
        Monster(std::string name, int screamPower);

        //getters
        std::string getName() const;
        int getscreamPower() const;

        static bool isLess(const Monster& a, const Monster& b);
        static bool isGreater(const Monster& a, const Monster& b);
        static bool isEqual(const Monster& a, const Monster& b);

    private:
        std::string name; // Name of monster
        int screamPower; // Power of monster scream
};

#endif