#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "constants.h"
#include "Weapon.h"

class Player {
public:
    // Constructor
    explicit Player(character_Type type);

    // Getter
    int getHealth() const;
    int getMaxHealth() const;
    int getDamage() const;
    int getGold() const;
    int getXp() const;
    int getLevel() const;
    std::string getTypeName() const;
    character_Type getType() const;
    std::shared_ptr<Weapon> getCurrentWeapon() const;
    bool isAlive() const;

    // Status
    bool isDefending;
    bool isStunned;

    // Actions
    void takeDamage(int amount);
    void heal(int amount);
    void defend();
    void addXp(int amount);
    void addGold(int amount);
    bool spendGold(int amount);
    void equipWeapon(std::shared_ptr<Weapon> newWeapon);
    void reset(); //
    void fullHeal();

    // Save/Load Game
    void saveState(std::ofstream& file) const;
    void loadState(std::ifstream& file, const std::vector<std::shared_ptr<Weapon>>& allWeapons);

private:
    void level_Up();
    void activate_Second_Wind();

    character_Type type;
    int health;
    int max_Health;
    int base_Damage;
    int gold;
    int exp;
    int level;
    std::shared_ptr<Weapon> current_Weapon;
    std::vector<std::shared_ptr<Weapon>> inventory;
    bool second_Wind_Used;
};

#endif //PLAYER_H
