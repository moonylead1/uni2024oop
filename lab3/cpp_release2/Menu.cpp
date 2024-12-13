#include "Menu.h"
#include <iostream>

void Menu::displayMenuOptions() {
    std::cout << "\n--- Team Management System ---" << std::endl;
    std::cout << "1. Add Team Member" << std::endl;
    std::cout << "2. View Team Members" << std::endl;
    std::cout << "3. Find Youngest and Oldest Players" << std::endl;
    std::cout << "4. Exit" << std::endl;
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