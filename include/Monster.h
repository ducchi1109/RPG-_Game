#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include "constants.h"

class Monster {
public:
    // Constructor
    Monster(std::string name, int level, int health, int damage, monster_Ability ability = monster_Ability::NONE);

    //Getter
    // Getters
    std::string getName() const;
    int getLevel() const;
    int getHealth() const;
    int getDamage() const;
    monster_Ability getAbility() const;
    bool isAlive() const;

    // Actions
    void takeDamage(int amount);
    void reset();

    // Monster Special Ability
    int dotTurns;
    int attackCounter;

private:
    std::string name;       //
    int level;          //
    int initialHealth;
    int health;         //
    int damage;         //
    monster_Ability ability; //

};

#endif //MONSTER_H
