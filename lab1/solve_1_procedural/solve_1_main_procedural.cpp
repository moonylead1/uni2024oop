// snake case no spagettis heheheh sigma

// В команду вводиться список гравців. Користувач обирає гравців, які
// вийдуть на поле. Програма виводить наймолодшого та найстаршого
// гравців. При ООП реалізації передбачити класи «Команда», «Гравець».

//should i use constans like MENU_SELECT_PLAYER = 1 ???? nah i dont like tho
//see no actual reasoning to put more .h files this one still not too messy
//and thats is procedural and not oop as i not using any classes or capsulations
//tdlist: break in more fnc + add error handling for wrong input for non int choice opt (still work with else not gonna do cin.fail())
//fine the youngest and oldest function and use it in menu

//lines 116-117 better but more harder to read so i leave that way it already is
//auto [youngest, oldest] = find_youngest_and_oldest_player(players);
//std::cout << "Youngest player: " << youngest << "\n";
//std::cout << "Oldest player: " << oldest << "\n";

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

std::pair<std::string, std::string> find_youngest_and_oldest_player(const std::vector<std::string>& players) {
    size_t min_age = std::numeric_limits<size_t>::max();
    std::string min_age_name;
    size_t max_age = 0;
    std::string max_age_name;

    for (const auto& player : players) {
        size_t age = std::stoul(player.substr(player.find_first_of(' ') + 1));
        if (age < min_age) {
            min_age = age;
            min_age_name = player.substr(0, player.find_first_of(' ')); 
        }
        if (age > max_age) {
            max_age = age;
            max_age_name = player.substr(0, player.find_first_of(' '));
        }
    }

    return {min_age_name, max_age_name};
}

void display_menu () {
    std::cout << "Menu:\n";
    std::cout << "1. Select a player to move\n";
    std::cout << "2. Show on deck players\n";
    std::cout << "3. Find the youngest and oldest player\n";
    std::cout << "4. Show all players info\n";
    std::cout << "5. Exit\n";
    
    std::cout << "Enter your choice: ";
}

void display_players_array_specific(const std::vector<std::string>& players) {
    for (size_t i = 0; i < players.size(); ++i) {
        std::cout << i + 1 << ". " << players[i].substr(0, players[i].find_first_of(' ')) << "\n";
    }
}

void display_players_full_info_array_specific(const std::vector<std::string>& players) {
    for (size_t i = 0; i < players.size(); ++i) {
        std::cout << i + 1 << ". " << players[i] << "\n";
    }
}

bool load_players(std::vector<std::string>& players, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Can't open file: " << filename << std::endl;
        return false;
    }

    std::string player;
    while (std::getline(file, player)) {
        players.push_back(player);
    }

    file.close();
    return true;
}

int main()
{
    std::vector<std::string> players;

    if (load_players(players, "players.txt")) {
        
        std::vector<std::string> selected_players;
        int choice;

        while (true) {
            //Menu
            display_menu();
            std::cin >> choice;
            // tasks for menu
            if (choice == 1) {
                std::cout << "Available players:\n";
                display_players_array_specific(players);
                std::cout << "Enter the number of the player to move: ";
                size_t player_choice;
                std::cin >> player_choice;

                if (player_choice > 0 && player_choice <= players.size()) {
                    selected_players.push_back(players[player_choice - 1]);
                    players.erase(players.begin() + player_choice - 1);
                    std::cout << "Player moved successfully.\n";
                } else {
                    std::cout << "Not valid option!\n";
                }
            } else if (choice == 2){
                std::cout << "On deck players:\n";
                display_players_array_specific(selected_players);
            }else if (choice == 3) {
                std::cout << "Youngest player: " << find_youngest_and_oldest_player(players).first << "\n";
                std::cout << "Oldest player: " << find_youngest_and_oldest_player(players).second << "\n"; 
            } else if (choice == 4){
                std::cout << "All players and their ages:\n";
                display_players_full_info_array_specific(players);
            } else if (choice == 5) {
                std::cout << "Exiting...\n";
                break;
            } else {
                std::cout << "Not valid option!\n";
            }
        }
    }
    return 0;
}

