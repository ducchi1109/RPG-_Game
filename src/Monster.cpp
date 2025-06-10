#include "../include/Monster.h"

Monster::Monster(std::string name, int level, int health, int damage, monster_Ability ability)
    : name(std::move(name)), level(level), health(health), damage(damage), ability(ability), dotTurns(0), attackCounter(0){}

std::string Monster::getName() const { return name; }
int Monster::getLevel() const { return level; }
int Monster::getHealth() const { return health; }
int Monster::getDamage() const { return damage; }
monster_Ability Monster::getAbility() const { return ability; }
bool Monster::isAlive() const { return health > 0; }

void Monster::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Monster::reset() {
    health = initialHealth;
    dotTurns = 0;
    attackCounter = 0;
}

