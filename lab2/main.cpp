//as i ve seen in task ill better use strcpy bc it is more efficient in understanding text docs

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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
            std::cout << "Show players\n";
            break;
        case 2:
            std::cout << "Show players in game\n";
            break;
        case 3:
            std::cout << "Show trainers\n";
            break;
        case 4:
            std::cout << "Move player to game\n";
            break;
        case 5:
            std::cout << "Add player\n";
            break;
        case 6:
            std::cout << "Remove player\n";
            break;
        case 7:
            std::cout << "Add trainer\n";
            break;
        case 8:
            std::cout << "Remove trainer\n";
            break;
        case 9:
            std::cout << "Show the youngest and oldest player\n";
            break;
        case 10:
            std::cout << "Exit\n";
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
//if (yes) load it


bool doc_loader_players_file() {
    std::ifstream file("Players_table.txt");
    if (!file.is_open()) {
        std::cout << "No players found. Creating file.\n";
        std::ofstream new_file("Players_table.txt");
        new_file << "Name:;Age:;Position:;Touchdowns:;Team:;"; //remove this after scanner implement
        new_file.close();
        return true;
    } else {
        std::cout << "Players found. File loaded.\n";
        file.close();
        return true;
    }
    
    //if some err will occur that will be linearly dropped here (we belive not this case)
    return false;
}

bool doc_loader_trainers_file() {
    std::ifstream file("Trainers_table.txt");
    if (!file.is_open()) {
        std::cout << "No trainers found. Creating file.\n";
        std::ofstream new_file("Trainers_table.txt");
        new_file << "Name:;"; //remove this after scanner implement
        new_file.close();
        return true;
    } else {
        std::cout << "Trainers found. File loaded.\n";
        file.close();
        return true;
    }
    
    //if some err will occur that will be linearly dropped here (we belive not this case)
    return false;
}

bool doc_loader_teams_file() {
    std::ifstream file("Teams_table.txt");
    if (!file.is_open()) {
        std::cout << "No teams found. Creating file.\n";
        std::ofstream new_file("Teams_table.txt");
        new_file << "Name:;"; //remove this after scanner implement
        new_file.close();
        return true;
    } else {
        std::cout << "Teams found. File loaded.\n";
        file.close();
        return true;
    }
    
    //if some err will occur that will be linearly dropped here (we belive not this case)
    return false;
}



//main function
//loop it with while(true) and doing the menu combined task;
int main() {
    //here we will implement function to load players, trainers, teams from file
    doc_loader_players_file();
    doc_loader_trainers_file();
    doc_loader_teams_file();

    while (true) {
        menu_event();
    }
    return 0;
}