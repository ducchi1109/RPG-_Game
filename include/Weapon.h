#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "constants.h"

class Weapon {
public:
    // Constructor
    Weapon(std::string name, int damage, int price, weapon_Ability ability = weapon_Ability::NONE);

    // Getter
    std::string getName() const;
    int getDamage() const;
    int getPrice() const;
    weapon_Ability getAbility() const;

private:
    std::string name;
    int damage;
    int price;
    weapon_Ability ability;
};

#endif //WEAPON_H
