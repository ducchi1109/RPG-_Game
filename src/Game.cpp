#include "../include/Game.h"

#include <iostream>
#include <random>
#include <limits>

Game::Game() : isRunning(true) {
    initialize_Data();
}

void Game::initialize_Data() {
    // Vũ khí
    allWeapons.push_back(std::make_shared<Weapon>("Stick", 5, 0));
    allWeapons.push_back(std::make_shared<Weapon>("Dagger", 15, 20));
    allWeapons.push_back(std::make_shared<Weapon>("Short Sword", 25, 50));
    allWeapons.push_back(std::make_shared<Weapon>("Long Sword", 35, 100));
    allWeapons.push_back(std::make_shared<Weapon>("Battle Axe", 45, 150));
    allWeapons.push_back(std::make_shared<Weapon>("War Hammer", 55, 200));
    allWeapons.push_back(std::make_shared<Weapon>("Enchanted Bow", 65, 300, weapon_Ability::CRITICAL_HIT));
    allWeapons.push_back(std::make_shared<Weapon>("Mystic Staff", 75, 400, weapon_Ability::DOUBLE_ATTACK));
    allWeapons.push_back(std::make_shared<Weapon>("Divine Blade", 100, 500, weapon_Ability::HEAL_ON_HIT));

    // Quái vật
    allMonsters.push_back(std::make_shared<Monster>("Slime", 2, 20, 5));
    allMonsters.push_back(std::make_shared<Monster>("Goblin", 4, 40, 10));
    allMonsters.push_back(std::make_shared<Monster>("Soi (Wolf)", 6, 55, 15));
    allMonsters.push_back(std::make_shared<Monster>("Orc", 8, 70, 20));
    allMonsters.push_back(std::make_shared<Monster>("Troll", 10, 85, 25));
    allMonsters.push_back(std::make_shared<Monster>("Minotaur", 12, 120, 30));
    allMonsters.push_back(std::make_shared<Monster>("Giant Spider", 14, 150, 35));
    allMonsters.push_back(std::make_shared<Monster>("Fire Dragon", 16, 200, 40, monster_Ability::DOT));
    allMonsters.push_back(std::make_shared<Monster>("Dark Knight", 18, 300, 45, monster_Ability::BREAK_DEFENSE));
    allMonsters.push_back(std::make_shared<Monster>("Ice Witch", 20, 450, 50, monster_Ability::STUN));
}

void Game::run() {
    while(isRunning) {
        main_Menu();
    }
}

void Game::main_Menu() {
    clear_Screen();
    std::cout << "=============================\n";
    std::cout << "       GAME NHAP VAI\n";
    std::cout << "=============================\n";
    std::cout << "1. Game Moi\n";
    std::cout << "2. Tai Game\n";
    std::cout << "3. Thoat\n";

    int choice = get_Choice(1, 3);
    switch(choice) {
        case 1:
            character_Selection();
            town_Square();
            break;
        case 2:
            load_Game();
            if (player) {
                town_Square();
            }
            break;
        case 3:
            isRunning = false;
            break;
        default:
            std::cout << "Invalid Choice" << std::endl;
            break;
    }
}

void Game::character_Selection() {
    clear_Screen();
    std::cout << "=============================\n";
    std::cout << "      CHON NHAN VAT\n";
    std::cout << "=============================\n";
    std::cout << "1. Tanker - Mau cao, sat thuong thap\n"; //
    std::cout << "2. Attacker - Sat thuong cao, mau trung binh\n"; //
    std::cout << "3. Magician - Hoi sinh mot lan\n"; //

    int choice = get_Choice(1, 3);
    player = std::make_unique<Player>(static_cast<character_Type>(choice - 1));
    player->equipWeapon(allWeapons[0]); // Trang bị Gậy
}

void Game::town_Square() {
    // Điểm bắt đầu
    while (player->isAlive() && isRunning) {
        clear_Screen();
        std::cout << "=============================\n";
        std::cout << "   QUANG TRUONG THI TRAN\n";
        std::cout << "=============================\n";
        print_Player_Status();
        std::cout << "-----------------------------\n";
        std::cout << "Ban co the:\n";
        std::cout << "1. Di den Cua hang\n"; //
        std::cout << "2. Di den Hang dong\n"; //
        std::cout << "3. CHIEN DAU VOI BOSS CUOI\n"; //
        std::cout << "4. Luu Game\n"; //
        std::cout << "5. Quay ve Menu Chinh\n";

        int choice = get_Choice(1, 5);
        switch (choice) {
            case 1: store(); break;
            case 2: cave(); break;
            case 3:
                start_Combat(*allMonsters.back());
                if(player->isAlive() && !allMonsters.back()->isAlive()) {
                    // Xử lý thắng game
                    isRunning = false;
                }
                break;
            case 4: save_Game(); break;
            case 5: return;
            default:
                std::cout << "Invalid Choice" << std::endl;
                break;
        }
    }
}

void Game::store() {
    while(player->isAlive()) {
        clear_Screen();
        std::cout << "=============================\n";
        std::cout << "           CUA HANG\n"; //
        std::cout << "=============================\n";
        print_Player_Status();
        std::cout << "-----------------------------\n";
        std::cout << "1. Mua mau (+20 mau) - 10 vang\n"; //
        std::cout << "2. Nang cap vu khi\n";
        std::cout << "3. Tro ve quang truong\n";

        int choice = get_Choice(1, 3);
        if (choice == 1) {
            if (player->spendGold(10)) {
                player->heal(20);
                std::cout << "Ban da mua mau!\n";
            } else {
                std::cout << "Khong du vang!\n";
            }
            wait_For_Enter();
        } else if (choice == 2) {
             while(true){
                clear_Screen();
                std::cout << "--- Nang Cap Vu Khi ---\n";
                print_Player_Status();
                std::cout << "-------------------\n";
                for (size_t i = 1; i < allWeapons.size(); ++i) {
                    std::cout << i << ". " << allWeapons[i]->getName() << " (" << allWeapons[i]->getDamage() << " DMG) - " << allWeapons[i]->getPrice() << " vang\n";
                }
                std::cout << allWeapons.size() << ". Quay lai\n";

                int weapon_Choice = get_Choice(1, allWeapons.size());
                if(weapon_Choice == static_cast<int>(allWeapons.size())) break;

                std::shared_ptr<Weapon> selected_Weapon = allWeapons[weapon_Choice];
                if(player->spendGold(selected_Weapon->getPrice())){
                    player->equipWeapon(selected_Weapon); //
                    std::cout << "Nang a thanh cong !" << selected_Weapon->getName() << "!\n";
                } else {
                    std::cout << "Khong du vang!\n";
                }
                wait_For_Enter();
            }
        } else if (choice == 3) {
            return;
        }
    }
}

void Game::cave() {
    while(player->isAlive()) {
        clear_Screen();
        std::cout << "=============================\n";
        std::cout << "          HANG DONG\n"; //
        std::cout << "=============================\n";
        print_Player_Status();
        std::cout << "-----------------------------\n";
        std::cout << "Chon quai vat de chien dau:\n";
        // Chỉ hiện quái vật thường, trừ boss cuối
        for (size_t i = 0; i < allMonsters.size() - 1; ++i) {
            std::cout << i + 1 << ". " << allMonsters[i]->getName() << " (Cap " << allMonsters[i]->getLevel() << ")\n"; //
        }
        std::cout << allMonsters.size() << ". Tro ve quang truong\n";

        int choice = get_Choice(1, allMonsters.size());
        if (choice == (int)allMonsters.size()) {
            return;
        }
        start_Combat(*allMonsters[choice-1]);
    }
}

void Game::start_Combat(Monster& monster) {
    monster.reset();
    player->isDefending = false;
    player->isStunned = false;

    while (player->isAlive() && monster.isAlive()) {
        // Lượt của người chơi
        if (!player->isStunned) {
            player_Turn(monster);
        } else {
            std::cout << "Ban bi choang va bo qua luot!\n";
            player->isStunned = false; // Hết choáng sau 1 lượt
            wait_For_Enter();
        }

        if (!monster.isAlive()) break;

        // Lượt của quái vật
        monster_Turn(monster);

        // Xử lý hiệu ứng DoT
        if (monster.dotTurns > 0) {
            std::cout << "Ban mat 5 mau do bi dot chay!\n";
            player->takeDamage(5);
            monster.dotTurns--;
            wait_For_Enter();
        }
    }

    // Kết thúc chiến đấu
    clear_Screen();
    if (player->isAlive()) {
        std::cout << "=============================\n";
        std::cout << "          CHIEN THANG!\n";
        std::cout << "=============================\n";
        std::cout << "Ban da ha guc " << monster.getName() << ".\n";

        if (monster.getName() == "Phu thuy bang (Ice Witch)") {
            std::cout << "\nXIN CHUC MUNG! BAN DA PHA DAO GAME!\n"; //
            wait_For_Enter();
            return;
        }

        int gold_Gained = monster.getLevel() * 10; //
        int exp_Gained = monster.getLevel() * 20; //
        player->addGold(gold_Gained);
        player->addXp(exp_Gained);
        std::cout << "Ban nhan duoc " << gold_Gained << " vang va " << exp_Gained << " XP.\n";
        wait_For_Enter();

        play_Mini_Game(); // Chơi mini-game sau mỗi trận thắng

    } else {
        std::cout << "=============================\n";
        std::cout << "           THAT BAI!\n";
        std::cout << "=============================\n";
        std::cout << "Ban da bi ha guc.\n";
        std::cout << "Tien trinh cua ban se duoc reset!\n"; //
        player->reset();
        player->equipWeapon(allWeapons[0]); // Trang bị lại vũ khí Gậy
        wait_For_Enter();
    }
}

void Game::player_Turn(Monster& monster) {
    clear_Screen();
    std::cout << "=============================\n";
    std::cout << "          CHIEN DAU\n"; //
    std::cout << "=============================\n";
    std::cout << "Ban vs. " << monster.getName() << " (HP: " << monster.getHealth() << ")\n";
    print_Player_Status();
    std::cout << "-----------------------------\n";
    std::cout << "1. Tan cong\n";
    std::cout << "2. Phong thu\n";

    int choice = get_Choice(1, 2);
    int total_Damage = 0;

    if (choice == 1) {
        total_Damage = player->getDamage() + player->getCurrentWeapon()->getDamage();

        // Xử lý nội tại vũ khí
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 100);
        int rand_chance = distrib(gen);

        weapon_Ability ability = player->getCurrentWeapon()->getAbility();
        if (ability == weapon_Ability::CRITICAL_HIT && rand_chance <= 30) {
            total_Damage *= 2;
            std::cout << "BAO KICH! Sat thuong x2!\n";
        }
        else if (ability == weapon_Ability::DOUBLE_ATTACK && rand_chance <= 40) { //
            int extraDamage = total_Damage / 2;
            std::cout << "DANH THEM! Gay them " << extraDamage << " sat thuong!\n";
            total_Damage += extraDamage;
        }
        else if (ability == weapon_Ability::HEAL_ON_HIT) { //
            int healedAmount = total_Damage * 0.3;
            player->heal(healedAmount);
            std::cout << "HUT MAU! Ban hoi " << healedAmount << " HP!\n";
        }

        std::cout << "Ban gay " << total_Damage << " sat thuong len " << monster.getName() << ".\n";
        monster.takeDamage(total_Damage);

    } else if (choice == 2) { // Phòng thủ
        player->defend();
        std::cout << "Ban vao the phong thu, giam 50% sat thuong nhan vao o luot tiep theo.\n";
    }
    wait_For_Enter();
}

void Game::monster_Turn(Monster& monster) {
    std::cout << monster.getName() << " tan cong!\n";
    int monster_Damage = monster.getDamage();

    // Xử lý nội tại quái vật
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);
    int rand_chance = distrib(gen);

    monster_Ability ability = monster.getAbility();
    if(ability == monster_Ability::BREAK_DEFENSE && rand_chance <= 40) { //
        if(player->isDefending){
             std::cout << "Hiep si bong toi PHA THE PHONG THU cua ban!\n";
             player->isDefending = false;
        }
    }
    else if (ability == monster_Ability::STUN && rand_chance <= 40) { //
        player->isStunned = true;
        std::cout << "Phu thuy bang lam CHOANG ban!\n";
    }
    else if(ability == monster_Ability::DOT) {
        monster.attackCounter++;
        if (monster.attackCounter % 3 == 0) { //
            monster.dotTurns = 3;
            std::cout << "Rong lua thieu dot ban!\n";
        }
    }

    player->takeDamage(monster_Damage);
    std::cout << monster.getName() << " gay " << monster_Damage << " sat thuong.\n";

    // Xử lý hồi sinh của Support sau khi nhận sát thương
    if (player->getHealth() == 1 && player->getType() == character_Type::Magician && player->isAlive()) {
        player->fullHeal(); // Hồi đầy máu vào đầu lượt tiếp theo
        std::cout << "Ban duoc hoi day mau nho Second Wind!\n";
    }
    wait_For_Enter();
}

void Game::play_Mini_Game() {
    clear_Screen();
    std::cout << "=============================\n";
    std::cout << "      MINI-GAME DOAN SO\n";
    std::cout << "=============================\n";
    std::cout << "Doan mot so tu 1 den 10: ";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 10);
    int randomNumber = distrib(gen);

    int guess = get_Choice(1, 10);

    if (guess == randomNumber) {
        if (distrib(gen) % 2 == 0) {
            player->addGold(50);
            std::cout << "Dung roi! Ban nhan duoc 50 vang!\n";
        } else {
            player->addXp(50);
            std::cout << "Dung roi! Ban nhan duoc 50 XP!\n";
        }
    } else {
        player->takeDamage(10);
        std::cout << "Sai roi! So dung la " << randomNumber << ". Ban mat 10 mau.\n";
        if (!player->isAlive()) {
            std::cout << "Ban da thua do het mau trong mini-game!\n";
        }
    }
    wait_For_Enter();
}

void Game::save_Game() {
    if(!player) {
        std::cout << "Khong co game de luu!\n";
        wait_For_Enter();
        return;
    }
    std::ofstream saveFile("../data/savegame.txt"); //
    if (saveFile.is_open()) {
        player->saveState(saveFile);
        saveFile.close();
        std::cout << "Da luu game thanh cong!\n";
    } else {
        std::cout << "Loi: Khong the mo file de luu.\n";
    }
    wait_For_Enter();
}

void Game::load_Game() {
    std::ifstream loadFile("../data/savegame.txt"); //
    if (loadFile.is_open()) {
        // Cần tạo một player tạm thời để load dữ liệu vào
        player = std::make_unique<Player>(character_Type::Tanker);
        player->loadState(loadFile, allWeapons);
        loadFile.close();
        std::cout << "Da tai game thanh cong!\n";
    } else {
        player.reset(); // Đảm bảo player là null nếu không tải được
        std::cout << "Khong tim thay file luu. Vui long bat dau game moi.\n"; //
    }
    wait_For_Enter();
}


// --- Helper Functions ---
void Game::clear_Screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Game::wait_For_Enter() {
    std::cout << "\nNhan Enter de tiep tuc...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(std::cin.rdbuf()->in_avail() > 0) { // Xử lý trường hợp buffer còn sót lại
        std::cin.get();
    } else {
        std::cin.get();
    }
}

void Game::print_Player_Status() {
    if (player) {
        std::cout << "Nhan vat: " << player->getTypeName() << " | Cap: " << player->getLevel() << "\n";
        std::cout << "Mau: " << player->getHealth() << "/" << player->getMaxHealth() << " | Sat thuong: " << player->getDamage() << "\n";
        std::cout << "Vang: " << player->getGold() << " | XP: " << player->getXp() << "/100\n";
        if(player->getCurrentWeapon())
            std::cout << "Vu khi: " << player->getCurrentWeapon()->getName() << " (+" << player->getCurrentWeapon()->getDamage() << " DMG)\n";
    }
}

int Game::get_Choice(int min, int max) {
    int choice;
    std::cout << "Lua chon cua ban (" << min << "-" << max << "): ";
    while (!(std::cin >> choice) || choice < min || choice > max) {
        std::cout << "Lua chon khong hop le. Vui long nhap mot so tu " << min << " den " << max << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}
