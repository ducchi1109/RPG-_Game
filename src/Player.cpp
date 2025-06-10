#include "../include/Player.h"

#include <iostream>
#include <sstream>
#include <utility>

Player::Player(character_Type type) : type(type), isDefending(false), isStunned(false) {
    switch (type) {
        case character_Type::Tanker:
            max_Health = 150;
            base_Damage = 10;
            break;
        case character_Type::Attacker:
            max_Health = 100;
            base_Damage = 20;
            break;
        case character_Type::Magician:
            max_Health = 100;
            base_Damage = 15;
            break;
    }
    health = max_Health;
    gold = 0;
    exp = 0;
    level = 1;
    second_Wind_Used = false;
}

int Player::getHealth() const { return health; }
int Player::getMaxHealth() const { return max_Health; }
int Player::getDamage() const { return base_Damage; }
int Player::getGold() const { return gold; }
int Player::getXp() const { return exp; }
int Player::getLevel() const { return level; }
std::shared_ptr<Weapon> Player::getCurrentWeapon() const { return current_Weapon; }
bool Player::isAlive() const { return health > 0; }
character_Type Player::getType() const { return type; }

std::string Player::getTypeName() const {
    switch (type) {
        case character_Type::Tanker: return "Tanker";
        case character_Type::Attacker: return "Attacker";
        case character_Type::Magician: return "Magician";
    }
    return "Unknown";
}

void Player::takeDamage(int amount) {
    if (isDefending) {
        amount /= 2; // Giảm 50% sát thương
        isDefending = false; // Trạng thái phòng thủ chỉ hiệu lực 1 lần
    }
    health -= amount;

    if (health <= 0) {
        health = 0;
        // Kiểm tra nội tại Second Wind
        if (type == character_Type::Magician && !second_Wind_Used) {
            activate_Second_Wind();
        }
    }
}

void Player::heal(int amount) {
    health += amount;
    if (health > max_Health) {
        health = max_Health;
    }
}

void Player::fullHeal() {
    health = max_Health;
}

void Player::defend() {
    isDefending = true;
}

void Player::addXp(int amount) {
    exp += amount;
    while (exp >= 100) {
        level_Up();
    }
}

void Player::level_Up() {
    exp -= 100; //
    level++;
    max_Health += 10; //
    base_Damage += 2; //
    health = max_Health; // Hồi đầy máu khi lên cấp
    std::cout << "\n*** DING! Ban da len cap " << level << "! ***\n";
}


void Player::addGold(int amount) {
    gold += amount;
}

bool Player::spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}

void Player::equipWeapon(std::shared_ptr<Weapon> newWeapon) {
    current_Weapon = std::move(newWeapon);
    inventory.push_back(current_Weapon);
}

void Player::reset() {
    // Reset tiến trình khi thua
    switch (type) {
        case character_Type::Tanker: max_Health = 150; base_Damage = 10; break;
        case character_Type::Attacker: max_Health = 100; base_Damage = 20; break;
        case character_Type::Magician: max_Health = 100; base_Damage = 15; break;
    }
    health = max_Health;
    gold = 0;
    exp = 0;
    level = 1;
    second_Wind_Used = false;
    inventory.clear();
}

void Player::activate_Second_Wind() {
    std::cout << "\n!!! Noi tai SECOND WIND da kich hoat! Ban se duoc hoi sinh! !!!\n";
    health = 1; // Đặt máu về 1
    second_Wind_Used = true; // Đánh dấu đã sử dụng
}

// Lưu trạng thái vào file
void Player::saveState(std::ofstream& file) const {
    file << "characterType:" << static_cast<int>(type) << "\n";
    file << "health:" << health << "\n";
    file << "maxHealth:" << max_Health << "\n";
    file << "baseDamage:" << base_Damage << "\n";
    file << "gold:" << gold << "\n";
    file << "xp:" << exp << "\n";
    file << "level:" << level << "\n";
    file << "secondWindUsed:" << second_Wind_Used << "\n";
    file << "currentWeapon:" << (current_Weapon ? current_Weapon->getName() : "None") << "\n";
    file << "inventory:";
    for (const auto& weapon : inventory) {
        file << weapon->getName() << ",";
    }
    file << "\n";
}

// Tải trạng thái từ file
void Player::loadState(std::ifstream& file, const std::vector<std::shared_ptr<Weapon>>& allWeapons) {
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string key;
        std::getline(ss, key, ':');

        if (key == "characterType") {
            int typeInt;
            ss >> typeInt;
            type = static_cast<character_Type>(typeInt);
        } else if (key == "health") {
            ss >> health;
        } else if (key == "maxHealth") {
            ss >> max_Health;
        } else if (key == "baseDamage") {
            ss >> base_Damage;
        } else if (key == "gold") {
            ss >> gold;
        } else if (key == "xp") {
            ss >> exp;
        } else if (key == "level") {
            ss >> level;
        } else if (key == "secondWindUsed") {
            ss >> second_Wind_Used;
        } else if (key == "currentWeapon") {
            std::string weaponName;
            std::getline(ss, weaponName);
            for (const auto& w : allWeapons) {
                if (w->getName() == weaponName) {
                    current_Weapon = w;
                    break;
                }
            }
        } else if (key == "inventory") {
            inventory.clear();
            std::string weaponName;
            while (std::getline(ss, weaponName, ',')) {
                if (!weaponName.empty()) {
                    for (const auto& w : allWeapons) {
                        if (w->getName() == weaponName) {
                            inventory.push_back(w);
                            break;
                        }
                    }
                }
            }
        }
    }
}