#include "Menu.h"
#include <iostream>

void Menu::displayMenuOptions() {
    std::cout << "\n--- Team Management System ---" << std::endl;
    std::cout << "1. Add Team Member" << std::endl;
    std::cout << "2. View Team Members" << std::endl;
    std::cout << "3. Find Youngest and Oldest Players" << std::endl;
    std::cout << "4. Select a Player" << std::endl;
    std::cout << "5. Show on-duty Players" << std::endl;
    std::cout << "6. Exit" << std::endl;
}

void Menu::showOnDutyPlayers() const {
    std::cout << "\n--- On-Duty Players ---" << std::endl;
    if (!onDutyPlayers.empty()) {
        for (const auto& player : onDutyPlayers) {
            std::cout << "Name: " << player->getName() << std::endl;
            std::cout << "Age: " << player->getAge() << " years" << std::endl;
            std::cout << "Goals: " << player->getGoals() << std::endl;
            std::cout << std::endl;
        }
    }else {
        std::cout << "No players on duty." << std::endl;
    }
}

void Menu::processUserChoice(int choice) {
    switch (choice) {
        case 1:
            team.addMember();
            break;
        case 2:
            team.viewTeam();
            break;
        case 3:
            team.findYoungestOldestPlayer();
            break;
        case 4:
            onDutyPlayers.push_back(team.selectPlayer());
            break;
        case 5:
            showOnDutyPlayers();
            break;
        case 6:
            exit(0);
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
    }
}

void Menu::run() {
    int choice;

    while (true) {
        displayMenuOptions();
        std::cout << "Select an option: ";
        std::cin >> choice;
        std::cin.ignore();

        processUserChoice(choice);
    }
}