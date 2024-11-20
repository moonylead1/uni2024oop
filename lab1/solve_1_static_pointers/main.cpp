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

bool load_players(std::vector<Player*>& players, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Can't open file: " << filename << std::endl;
        return false;
    }

    std::string player_str;
    while (std::getline(file, player_str)) {
        Player* new_player = new Player(player_str); // allocate new player
        players.push_back(new_player);
    }

    file.close();
    return true;
}

int main()
{
    std::vector<Player*> players;
    if (load_players(players, "players.txt")) {
        std::cout << "Players loaded successfully:\n";
    } else {
        std::cerr << "Failed to load players.\n";
        return 1; //we will throw error and end here
    }


    
    Team main_team("Main Team"); // create main team
    for (auto player : players) {
        main_team.add_player(player);
    }
    players.clear(); //clear the temp vector not deleting the players

    Team selection_team("Selection Team"); //  create selected players team

    std::cout << "Team name: " << main_team.get_name() << " loaded successfully!\n";

    for (const auto& player : main_team.get_players()) {
        std::cout << player->get_name() << " " << player->get_age() << "\n";
    }

    

    while(true){
        display_menu();
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "Current team not on deck:\n";
            for (size_t i = 0; i < main_team.get_players().size(); ++i) {
                std::cout << i + 1 << ". " << main_team.get_players()[i]->get_name() << "\t\t Age: " << main_team.get_players()[i]->get_age() << "\n";
            }
        } else if (choice == 2) {
            std::cout << "Available players:\n";
            for (size_t i = 0; i < main_team.get_players().size(); ++i) {
                std::cout << i + 1 << ". " << main_team.get_players()[i]->get_name() << "\t\t Age: " << main_team.get_players()[i]->get_age() << "\n";
            }
            std::cout << "Enter the number of the player to move: ";
            size_t player_choice;
            std::cin >> player_choice;

            if (player_choice > 0 && player_choice <= main_team.size()) {
                // get the player to move
                const Player* player_to_move = main_team.get_player(player_choice - 1);
        
                // pointer for sele team
                // We need this because we're transferring ownership
                Player* mutable_player = const_cast<Player*>(player_to_move);
        
                // add player to selection team
                selection_team.add_player(mutable_player);
        
                // remove player from original team not deleting it
                main_team.remove_player(player_choice - 1);
        
                std::cout << "Player moved successfully.\n";
            } else {
                std::cout << "Invalid option!\n";
            }

            
        } else if (choice == 3) {
            std::cout << "Players on deck:\n";
            for (size_t i = 0; i < selection_team.get_players().size(); ++i) {
                std::cout << i + 1 << ". " << selection_team.get_players()[i]->get_name() << "\t\t Age: " << selection_team.get_players()[i]->get_age() << "\n";
            }
        } else if (choice == 4) {
            std::cout << "Youngest player: " << main_team.get_youngest_player()->get_name() << ", his age is: "<< main_team.get_youngest_player()->get_age() <<"\n";
            std::cout << "Oldest player: " << main_team.get_oldest_player()->get_name() << ", his age is: "<< main_team.get_oldest_player()->get_age() << "\n";
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid option!\n";
        }

        pause();

        
    }
    return 0;
}
