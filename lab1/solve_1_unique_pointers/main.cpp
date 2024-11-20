// over all no more manual memory managment
// leaks preventized with smart pointers as bc auto cleanup
#include "Team.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include <memory>

void pause() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void display_menu() {
    std::cout << "Menu:\n";
    std::cout << "1. Show main team info\n";
    std::cout << "2. Select a player to move\n";
    std::cout << "3. Show on deck players\n";
    std::cout << "4. Find the youngest and oldest player\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice: ";
}

bool load_players(Team& team, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Can't open file: " << filename << std::endl;
        return false;
    }

    std::string player_str;
    while (std::getline(file, player_str)) {
        auto new_player = std::make_unique<Player>(player_str); //used make uniq to create new player
        team.add_player(std::move(new_player));
    }

    file.close();
    return true;
}

int main() {
    Team main_team("Main Team");
    if (!load_players(main_team, "players.txt")) {
        std::cerr << "Failed to load players.\n";
        return 1;
    }

    std::cout << "Team name: " << main_team.get_name() << " loaded successfully!\n";
    for (const auto& player : main_team.get_players()) {
        std::cout << player->get_name() << " " << player->get_age() << "\n";
    }

    Team selection_team("Selection Team");

    while (true) {
        display_menu();
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Current team not on deck:\n";
            const auto& players = main_team.get_players();
            for (size_t i = 0; i < players.size(); ++i) {
                std::cout << i + 1 << ". " << players[i]->get_name() << "\t\t Age: " << players[i]->get_age() << "\n";
            }
        } 
        else if (choice == 2) {
            std::cout << "Available players:\n";
            const auto& players = main_team.get_players();
            for (size_t i = 0; i < players.size(); ++i) {
                std::cout << i + 1 << ". " << players[i]->get_name() << "\t\t Age: " << players[i]->get_age() << "\n";
            }
            
            std::cout << "Enter the number of the player to move: ";
            size_t player_choice;
            std::cin >> player_choice;

            if (player_choice > 0 && player_choice <= main_team.size()) {
                // ownership transfer is explicit thru std::move
                // Move the player from main team to selection team
                auto player = main_team.remove_player(player_choice - 1);
                selection_team.add_player(std::move(player)); //modified transfer logic to use std::move
                std::cout << "Player moved successfully.\n";
            } else {
                std::cout << "Invalid option!\n";
            }
        }
        else if (choice == 3) {
            std::cout << "Players on deck:\n";
            const auto& players = selection_team.get_players();
            for (size_t i = 0; i < players.size(); ++i) {
                std::cout << i + 1 << ". " << players[i]->get_name() << "\t\t Age: " << players[i]->get_age() << "\n";
            }
        }
        else if (choice == 4) {
            if (const Player* youngest = main_team.get_youngest_player()) { //wrapped this up
                std::cout << "Youngest player: " << youngest->get_name() << ", his age is: " << youngest->get_age() << "\n";
            }
            if (const Player* oldest = main_team.get_oldest_player()) { // wrapped this same way as above
                std::cout << "Oldest player: " << oldest->get_name() << ", his age is: " << oldest->get_age() << "\n";
            }
        }
        else if (choice == 5) {
            break;
        }
        else {
            std::cout << "Invalid option!\n";
        }

        pause();
    }
    return 0;
}