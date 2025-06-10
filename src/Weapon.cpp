#include "../include/Weapon.h"

Weapon::Weapon(std::string name,  int damage,  int price,  weapon_Ability ability)
    : name(std::move(name)), damage(damage), price(price), ability(ability) {}

std::string Weapon::getName() const { return name; }
int Weapon::getDamage() const { return damage; }
int Weapon::getPrice() const { return price; }
weapon_Ability Weapon::getAbility() const { return ability; }