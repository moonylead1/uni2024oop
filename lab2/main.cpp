//as i ve seen in task ill better use strcpy bc it is more efficient in understanding text docs
#include "Team.h"
#include "Trainer.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//globals:
std::vector<Team> teams;
std::vector<Trainer> trainers;
std::vector<Player> players;

Team team_none("No_team", std::vector<Player>(), Trainer(""));

//menu must contain: 
//1. SHOW : show players (showing the table with all players currently written down in file)
//2. SHOW : trainers (same above)
//3. PLAYER : add player with all options as name, age, position, touchdowns (goals, assists) (btw pair maybe), team
// [name age position touchdowns team]
//4. PLAYER : remove player
//5. TRAINER : add trainer (trainer must have a name and a team based)
// [name team]
//6. TRAINER : remove trainer
//7. FUNC : show the youngest and oldest player
//8. OPER : EXIT

void menu_display() {
    std::cout << "Menu:\n";
    std::cout << "1.\tShow players\n";
    std::cout << "2.\tShow players in game\n";
    std::cout << "3.\tShow trainers\n";
    std::cout << "4.\tMove player to game\n";
    std::cout << "5.\tAdd player\n";
    std::cout << "6.\tRemove player\n";
    std::cout << "7.\tAdd trainer\n";
    std::cout << "8.\tRemove trainer\n";
    std::cout << "9.\tShow the youngest and oldest player\n";
    std::cout << "10.\tExit\n";
    std::cout << "Enter your choice: ";
}

//menu actions with its respective tasks
void menu_action(int choice) {
    switch (choice) {
        case 1:
            std::cout << "Show players -> List of players:\n";
            if (players.empty()) {
                std::cout << "Players list is empty. Try creating a player first.\n";
                break;
            } else {
                for (const auto& player : players) {
                    std::cout << player.get_name() << "\t" << player.get_age() << "\t" << player.get_position() << "\t" << player.get_touchdowns() << "\t" << player.get_team().get_name() << std::endl;
                }
            }
            break;
        case 2:
            std::cout << "Show players in game -> List of players in-game:\n";
            if (players.empty()) {
                std::cout << "Players list is empty. Try creating a player first.\n";
                break;
            } else {
                int found_status = 0;
                for (const auto& player : players) {
                    if (player.get_ingame() == true) {
                        std::cout << player.get_name() << "\t" << player.get_age() << "\t" << player.get_position() << "\t" << player.get_touchdowns() << "\t" << player.get_team().get_name() << std::endl;
                    }
                }
                if (found_status == 0) {
                    std::cout << "No players in game at the moment. Try to moving at least one player to game.\n";
                }
            }
            break;
        case 3:
            std::cout << "Show trainers -> List of trainers:\n";
            if (trainers.empty()) {
                std::cout << "Trainers list is empty. Try creating a trainer first.\n";
                break;
            } else {
                for (const auto& trainer : trainers) {
                    std::cout << trainer.get_name() << std::endl;
                }
            }
            break;
        case 4:
            std::cout << "Move player to game -> Moving player: \n";
            if (players.empty()) {
                std::cout << "Players list is empty. Try creating a player first.\n";
                break;
            } else { 
                int choice;
                std::cout << "Enter player number: ";
                for (int i = 0; i < players.size(); i++) {
                    std::cout << i + 1 << ". " << players[i].get_name() << std::endl;
                }
                std::cin >> choice;
                if (choice < 1 || choice > players.size()) {
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }
                players[choice - 1].set_ingame(true);
                std::cout << "Player " << players[choice - 1].get_name() << " has been moved to game.\n"; 
            }
            break;
        case 5: { // using block here
            std::cout << "Add player -> Adding player:\n";
            std::string option;
            do {
                std::string name, position, team;
                int age, touchdowns;
                std::cout << "Enter player name: ";
                std::getline(std::cin, name);
                std::cout << "Enter player age: ";
                std::cin >> age;
                std::cout << "Enter player position: ";
                std::getline(std::cin, position);
                std::cout << "Enter player touchdowns: ";
                std::cin >> touchdowns;
                std::cout << "Enter player team: ";
                std::getline(std::cin, team);

                int found_team = -1;
                for (int i = 0; i < teams.size(); i++) {
                    if (teams[i].get_name() == team) {
                        found_team = i;
                        break;
                    }
                }
                if (found_team == -1) {
                    Player player(name, age, position, touchdowns, team_none, false);
                    players.push_back(player);
                } else { 
                    Player player(name, age, position, touchdowns, teams[found_team], false);
                    players.push_back(player);
                }
                
                std::cout << "Do you want to add another player? (yes/no): ";
                std::getline(std::cin, option);
            } while (option != "no" && option != "No" && option != "NO" && option != "n" && option != "N");
            break;
            }
        case 6:
            std::cout << "Remove player -> Removing player: \n";
            if (players.empty()) {
                std::cout << "Players list is empty, no way you can remove nothing. Try creating a player first.\n";
            } else {
                int choice;
                std::cout << "Enter player number: ";
                for (int i = 0; i < players.size(); i++) {
                    std::cout << i + 1 << ". " << players[i].get_name() << std::endl;
                }
                std::cin >> choice;
                if (choice < 1 || choice > players.size()) {
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }
                players.erase(players.begin() + choice - 1);
                std::cout << "Player " << players[choice - 1].get_name() << " has been removed.\n";
            }
            break;
        case 7: {
            std::cout << "Add trainer -> Adding trainer: \n";
            std::string name;
            std::cout << "Enter trainer name: ";
            std::getline(std::cin, name);
            Trainer trainer(name);
            trainers.push_back(trainer);
            std::cout << "Trainer " << name << " has been added.\n";
            }
            break;
        case 8:
            std::cout << "Remove trainer -> Removing trainer:\n";
            if (trainers.empty()) {
                std::cout << "Trainers list is empty, no way you can remove nothing. Try creating a trainer first.\n";
            } else {
                int choice;
                std::cout << "Enter trainer number: ";
                for (int i = 0; i < trainers.size(); i++) {
                    std::cout << i + 1 << ". " << trainers[i].get_name() << std::endl;
                }
                std::cin >> choice;
                if (choice < 1 || choice > trainers.size()) {
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }
                trainers.erase(trainers.begin() + choice - 1);
                std::cout << "Trainer " << trainers[choice - 1].get_name() << " has been removed.\n";
            }
            break;
        case 9:
            std::cout << "Show the youngest and oldest player -> The youngest and oldest player are:\n";
            if (players.size() < 2) {
                std::cout << "Players list is empty. Try creating at least two players first.\n";
                break;
            } else {
                int min_age = players[0].get_age();
                int max_age = players[0].get_age();
                std::string min_name = players[0].get_name();
                std::string max_name = players[0].get_name();
                for (const auto& player : players) {
                    if (player.get_age() < min_age) {
                        min_age = player.get_age();
                        min_name = player.get_name();
                    }
                    if (player.get_age() > max_age) {
                        max_age = player.get_age();
                        max_name = player.get_name();
                    }
                }
                std::cout << "Youngest player: " << min_name << " age is: " << min_age << std::endl;
                std::cout << "Oldest player: " << max_name << " age is: " << max_age << std::endl;
            }
            break;
        case 10: {
            std::cout << "Exit\n";
            std::cout << "Are you sure you want to exit? (yes/no): ";
            std::string option;
            std::getline(std::cin, option);
            if (option == "yes" || option == "Yes" || option == "YES" || option == "y" || option == "Y") {
                exit(0);
            }
            }
            break;
        default:
            std::cout << "Invalid choice! Check your input.\n";
            break;
    }
}

//menu combined startup
void menu_event() {
    menu_display();
    int user_choice;
    std::cin >> user_choice;
    menu_action(user_choice);
}

//Text Docs Scan
//idea for txt files recognition
//if (no) file located in folder create it with template in it and show all time void that no players found: 
//if (yes) load it with checking (how idk we will see in stup function)


bool doc_loader_players_file() {
    std::ifstream file("Players_table.txt");
    if (!file.is_open()) {
        std::cout << "No players found. Creating file.\n";
        std::ofstream new_file("Players_table.txt");
        new_file.close();
        return true;
    } else {
        std::cout << "Players found. File loaded.\n";
        file.close();
        return false;
    }
}

bool doc_loader_trainers_file() {
    std::ifstream file("Trainers_table.txt");
    if (!file.is_open()) {
        std::cout << "No trainers found. Creating file.\n";
        std::ofstream new_file("Trainers_table.txt");
        new_file.close();
        return true;
    } else {
        std::cout << "Trainers found. File loaded.\n";
        file.close();
        return false;
    }
}

bool doc_loader_teams_file() {
    std::ifstream file("Teams_table.txt");
    if (!file.is_open()) {
        std::cout << "No teams found. Creating file.\n";
        std::ofstream new_file("Teams_table.txt");
        new_file.close();
        return true;
    } else {
        std::cout << "Teams found. File loaded.\n";
        file.close();
        return false;
    }
}

//docs setup functions
bool doc_setup_teams_file() {
    std::ifstream file("Teams_table.txt");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            size_t found = line.find("name:");
            if (found != std::string::npos) {
                std::string name = line.substr(found + 5);
                found = name.find(";");
                if (found != std::string::npos) {
                    name = name.substr(0, found);
                    Team team(name, std::vector<Player>(), Trainer(""));
                    teams.push_back(team);
                }
            }
        }
        file.close();
    }
}


bool doc_setup_players_file() { //holy fuck pls work itryharded too much
    std::ifstream file("Players_table.txt");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            size_t found = line.find("Name:");
            if (found != std::string::npos) {
                std::string name = line.substr(found + 5);
                found = name.find(";");
                if (found != std::string::npos) {
                    name = name.substr(0, found);
                    found = line.find("Age:");
                    if (found != std::string::npos) {
                        std::string age = line.substr(found + 4);
                        found = age.find(";");
                        if (found != std::string::npos) {
                            age = age.substr(0, found);
                            found = line.find("Position:");
                            if (found != std::string::npos) {
                                std::string position = line.substr(found + 9);
                                found = position.find(";");
                                if (found != std::string::npos) {
                                    position = position.substr(0, found);
                                    found = line.find("Touchdowns:");
                                    if (found != std::string::npos) {
                                        std::string touchdowns = line.substr(found + 11);
                                        found = touchdowns.find(";");
                                        if (found != std::string::npos) {
                                            touchdowns = touchdowns.substr(0, found);
                                            if (found != std::string::npos) {
                                                found = line.find("Team:");
                                                if (found != std::string::npos) {
                                                    std::string team = line.substr(found + 5);
                                                    found = team.find(";");
                                                    if (found != std::string::npos) {
                                                        team = team.substr(0, found);
                                                        bool found_team = false;
                                                        for (auto& t : teams) {
                                                            if (t.get_name() == team) {
                                                                Player player(name, std::stoi(age), position, std::stoi(touchdowns), t, false);
                                                                players.push_back(player);
                                                                found_team = true;
                                                                break;
                                                            }
                                                        }
                                                        if (!found_team){
                                                            Player player(name, std::stoi(age), position, std::stoi(touchdowns), team_none, false);
                                                            team_none.get_players().push_back(player);
                                                            players.push_back(player);
                                                        }
                                                    }
                                                }
                                            }
                                            
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        file.close();
    }
}

bool doc_setup_trainers_file() {
    std::ifstream file("Trainers_table.txt");
    std::string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            size_t found = line.find("Name:");
            if (found != std::string::npos) {
                std::string name = line.substr(found + 5);
                found = name.find(";");
                if (found != std::string::npos) {
                    name = name.substr(0, found);
                    Trainer trainer(name);
                    trainers.push_back(trainer);
                    found = line.find("Team:");
                    if (found != std::string::npos) {
                        std::string team = line.substr(found + 5);
                        found = team.find(";");
                        if (found != std::string::npos) {
                            team = team.substr(0, found);
                            bool found_team = false;
                            for (auto& t : teams) {
                                if (t.get_name() == team) {
                                    t.set_trainer(trainer);
                                    found_team = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        file.close();
    }
}



//main function
//loop it with while(true) and doing the menu combined task;
int main() {
    //here we will implement function to load players, trainers, teams from file or creating the new ones)
    //start up operations

    //check-marks if files are empty
    bool doc_teams_loaded_empty = false;
    bool doc_players_loaded_empty = false;
    bool doc_trainers_loaded_empty = false;

    //loading files
    if(doc_loader_teams_file()){
        std::cout<< "file Teams_table.txt missing, we have created a new one...";
        doc_teams_loaded_empty = true;
    } else if (std::ifstream("Teams_table.txt").peek() == std::ifstream::traits_type::eof()) { // check if file created but empty
        std::cout << "file Teams_table.txt is empty, don't worry, you will fill it later...";
        doc_teams_loaded_empty = true; 
    } else {
        std::cout << "Teams found.\n";
        std::cout << "Loading file...\n";
        doc_setup_teams_file();
        std::cout << "File Teams_table.txt loaded.\n";
    }

    if(doc_loader_players_file()){ std::cout<< "file Players_table.txt loaded with error, we have created a new one...";
        doc_players_loaded_empty = true;
    } else if (std::ifstream("Players_table.txt").peek() == std::ifstream::traits_type::eof()) { // check if file created but empty
        std::cout << "file Players_table.txt is empty, don't worry, you will fill it later...";
        doc_players_loaded_empty = true;
    } else {
        std::cout << "Players found.\n";
        std::cout << "Loading file...\n";
        doc_setup_players_file();
        std::cout << "File Players_table.txt loaded.\n";
    }

    if(doc_loader_trainers_file()){
        std::cout<< "file Trainer_table.txt loaded with error, we have created a new one...";
        doc_trainers_loaded_empty = true;
    } else if (std::ifstream("Trainers_table.txt").peek() == std::ifstream::traits_type::eof()) { // check if file created but empty
        std::cout << "file Trainers_table.txt is empty, don't worry, you will fill it later...";
        doc_trainers_loaded_empty = true;
    }else {
        std::cout << "Trainers found.\n";
        std::cout << "Loading file...\n";
        doc_setup_trainers_file();
        std::cout << "File Trainers_table.txt loaded.\n";
    }

    

    //loop
    while (true) {
        menu_event();
    }
    return 0;
}