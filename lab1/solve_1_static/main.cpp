#include "Team.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>


void pause() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}


void display_menu () {
    std::cout << "Menu:\n";
    std::cout << "1. Show main team info\n";
    std::cout << "2. Select a player to move\n";
    std::cout << "3. Show on deck players\n";
    std::cout << "4. Find the youngest and oldest player\n";
    std::cout << "5. Exit\n";
    
    std::cout << "Enter your choice: ";
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
        std::cout << "Players loaded successfully:\n";
    } else {
        std::cerr << "Failed to load players.\n"; //linked to standart error stream
    }

    
    std::vector<Player> team; //here i created a team vector that holds players will move to team.h
    for (const auto& player : players) { 
        Player new_player(player);
        team.push_back(new_player);
    }

    Team new_team("Red Team", team); //created a team object
    std::cout << "Team name: " << new_team.get_name() << " loaded successfully!\n";

    for (const auto& player : new_team.get_players()) {
        std::cout << player.get_name() << " " << player.get_age() << "\n";
    }

    Team selection_team("Selection Team", {}); // this is players on deck

    while(true){
        display_menu();
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "Current team not on deck:\n";
            for (size_t i = 0; i < new_team.get_players().size(); ++i) {
                std::cout << i + 1 << ". " << new_team.get_players()[i].get_name() << "\t\t Age: " << new_team.get_players()[i].get_age() << "\n";
            }
        } else if (choice == 2) {
            std::cout << "Available players:\n";
            for (size_t i = 0; i < new_team.get_players().size(); ++i) {
                std::cout << i + 1 << ". " << new_team.get_players()[i].get_name() << "\t\t Age: " << new_team.get_players()[i].get_age() << "\n";
            }
            std::cout << "Enter the number of the player to move: ";
            size_t player_choice;
            std::cin >> player_choice;

            if (player_choice > 0 && player_choice <= new_team.size()) {
                // get the player to move
                const Player& player_to_move = new_team.get_player(player_choice - 1);
                
                // add player to selection team
                selection_team.add_player(player_to_move);
                
                // remove player from original team
                new_team.remove_player(player_choice - 1);
                
                std::cout << "Player moved successfully.\n";
            } else {
                std::cout << "Invalid option!\n";
            }

            
        } else if (choice == 3) {
            std::cout << "Players on deck:\n";
            for (size_t i = 0; i < selection_team.get_players().size(); ++i) {
                std::cout << i + 1 << ". " << selection_team.get_players()[i].get_name() << "\t\t Age: " << selection_team.get_players()[i].get_age() << "\n";
            }
        } else if (choice == 4) {
            std::cout << "Youngest player: " << new_team.get_youngest_player().get_name() << ", his age is: "<< new_team.get_youngest_player().get_age() <<"\n";
            std::cout << "Oldest player: " << new_team.get_oldest_player().get_name() << ", his age is: "<< new_team.get_oldest_player().get_age() << "\n";
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid option!\n";
        }

        pause();

        
    }
    return 0;
}
