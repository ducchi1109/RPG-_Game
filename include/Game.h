#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "Player.h"
#include "Monster.h"
#include "Weapon.h"

class Game {
public:
    Game();
    void run();

private:
    void initialize_Data();
    void main_Menu();
    void character_Selection();
    void town_Square();
    void store();
    void cave();
    void start_Combat(Monster& monster);
    void player_Turn(Monster& monster);
    void monster_Turn(Monster& monster);
    void play_Mini_Game();
    void save_Game();
    void load_Game();

    // Helpers
    void clear_Screen();
    void wait_For_Enter();
    void print_Player_Status();

    static int get_Choice(int min, int max);

    std::unique_ptr<Player> player;
    std::vector<std::shared_ptr<Weapon>> allWeapons;
    std::vector<std::shared_ptr<Monster>> allMonsters;
    bool isRunning;
};

#endif //GAME_H
