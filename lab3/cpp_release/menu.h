#ifndef MENU_H
#define MENU_H

#include "team.h"
#include "file_manager.h"

class Menu {
public:
    void display_main_menu() {
        std::cout << "\n--- Team Management System ---" << std::endl;
        std::cout << "1. Add Team Member" << std::endl;
        std::cout << "2. View Team Members" << std::endl;
        std::cout << "3. Find Youngest and Oldest Players" << std::endl;
        std::cout << "4. Exit" << std::endl;
    }

    int get_user_choice() {
        int choice;
        std::cout << "Select an option: ";
        std::cin >> choice;
        std::cin.ignore();
        return choice;
    }

    void add_team_member(Team& team, FileManager& file_manager) {
        std::string member_type, name, birthdate, additional_info;

        std::cout << "Enter member type (Player/Coach): ";
        std::getline(std::cin, member_type);

        std::cout << "Enter name: ";
        std::getline(std::cin, name);

        std::cout << "Enter birthdate (DD.MM.YYYY): ";
        std::getline(std::cin, birthdate);

        if (member_type == "Player") {
            int goals;
            std::cout << "Enter number of goals in career: ";
            std::cin >> goals;
            std::cin.ignore();
            team.add_player(name, birthdate, goals);
        } else if (member_type == "Coach") {
            std::cout << "Enter category: ";
            std::getline(std::cin, additional_info);
            team.add_coach(name, birthdate, additional_info);
        }

        file_manager.save_team_members(team.get_members());
        std::cout << "Team member added successfully!" << std::endl;
    }
};

#endif // MENU_H