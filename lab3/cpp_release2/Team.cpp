#include "Team.h"
#include "Player.h"
#include "Coach.h"
#include "TeamMember.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Team::Team(const std::string& filename) : filename(filename) {
    loadMembers();
}

Team::~Team() {
    for (auto member : members) {
        delete member;
    }
}

void Team::loadMembers() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string type, name, birthdateStr, additional;
        
        // Ensure we can parse all components
        if (!(std::getline(ss, type, ';') && 
              std::getline(ss, name, ';') && 
              std::getline(ss, birthdateStr, ';') && 
              std::getline(ss, additional))) {
            std::cerr << "Malformed line: " << line << std::endl;
            continue;
        }

        if (type == "Player") {
            try {
                int goals = std::stoi(additional);
                members.push_back(new Player(name, birthdateStr, goals));
            } catch (const std::exception& e) {
                std::cerr << "Error parsing player: " << e.what() << std::endl;
            }
        } else if (type == "Coach") {
            members.push_back(new Coach(name, birthdateStr, additional));
        }
    }
}

void Team::saveMembers() {
    std::ofstream file(filename);
    for (const auto& member : members) {
        file << member->getDetailsForSave() << std::endl;
    }
}

void Team::addMember() {
    std::string type, name, birthdate, additional;
    std::cout << "Enter member type (Player/Coach): ";
    std::getline(std::cin, type);
    
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter birthdate (DD.MM.YYYY): ";
    std::getline(std::cin, birthdate);

    if (type == "Player") {
        int goals;
        std::cout << "Enter number of goals in career: ";
        std::cin >> goals;
        std::cin.ignore();
        
        members.push_back(new Player(name, birthdate, goals));
    } else if (type == "Coach") {
        std::cout << "Enter category: ";
        std::getline(std::cin, additional);
        
        members.push_back(new Coach(name, birthdate, additional));
    }

    saveMembers();
    std::cout << "Team member added successfully!" << std::endl;
}

void Team::viewTeam() {
    if (members.empty()) {
        std::cout << "Team is empty." << std::endl;
        return;
    }

    std::cout << "\n--- Team Members ---" << std::endl;
    for (const auto& member : members) {
        std::cout << "\nType: " << member->getType() << std::endl;
        std::cout << "Name: " << member->getName() << std::endl;
        
        char buffer[80];
        std::tm birthdate_tm = member->getBirthdate();
        std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", &birthdate_tm);
        std::cout << "Birthdate: " << buffer << std::endl;
        
        std::cout << "Age: " << member->getAge() << " years" << std::endl;

        if (auto* player = dynamic_cast<Player*>(member)) {
            std::cout << "Career Goals: " << player->getGoals() << std::endl;
        } else if (auto* coach = dynamic_cast<Coach*>(member)) {
            std::cout << "Category: " << coach->getCategory() << std::endl;
        }
    }
}

void Team::findYoungestOldestPlayer() {
    std::vector<Player*> players;
    for (const auto& member : members) {
        if (auto* player = dynamic_cast<Player*>(member)) {
            players.push_back(player);
        }
    }

    if (players.empty()) {
        std::cout << "No players in the team." << std::endl;
        return;
    }

    // More robust comparison using a custom function
    auto compare_birthdate = [](const Player* a, const Player* b) {
        // Adjust for 1900-based year representation in std::tm
        int year_a = a->getBirthdate().tm_year + 1900;
        int year_b = b->getBirthdate().tm_year + 1900;
        
        // Compare years first
        if (year_a != year_b) {
            return year_a > year_b;  // Younger player has later year
        }
        
        // If years are same, compare months (0-11)
        if (a->getBirthdate().tm_mon != b->getBirthdate().tm_mon) {
            return a->getBirthdate().tm_mon > b->getBirthdate().tm_mon;
        }
        
        // If months are same, compare days
        return a->getBirthdate().tm_mday > b->getBirthdate().tm_mday;
    };

    // Find youngest (latest birthdate)
    auto youngest = *std::min_element(players.begin(), players.end(), compare_birthdate);

    // Find oldest (earliest birthdate)
    auto oldest = *std::max_element(players.begin(), players.end(), compare_birthdate);

    // Detailed output
    std::cout << "\n--- Youngest and Oldest Players ---" << std::endl;
    
    // Youngest Player details
    std::cout << "Youngest Player:" << std::endl;
    std::cout << "Name: " << youngest->getName() << std::endl;
    
    char buffer[80];
    std::tm youngest_tm = youngest->getBirthdate();
    // Adjusted format to match your input/output expectation
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", &youngest_tm);
    std::cout << "Birthdate: " << buffer << std::endl;
    
    std::cout << "Age: " << youngest->getAge() << " years" << std::endl;
    std::cout << "Career Goals: " << youngest->getGoals() << std::endl;

    // Oldest Player details
    std::cout << "\nOldest Player:" << std::endl;
    std::cout << "Name: " << oldest->getName() << std::endl;
    
    std::tm oldest_tm = oldest->getBirthdate();
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", &oldest_tm);
    std::cout << "Birthdate: " << buffer << std::endl;
    
    std::cout << "Age: " << oldest->getAge() << " years" << std::endl;
    std::cout << "Career Goals: " << oldest->getGoals() << std::endl;
}