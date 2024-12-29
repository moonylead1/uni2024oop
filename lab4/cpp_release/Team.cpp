#include "Team.h"
#include "Player.h"
#include "Coach.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>

Team::Team(const std::string& filename) : filename(filename) {
    validateFile();
    loadMembers();
}

Team::~Team() {
    for (auto member : members) {
        delete member;
    }
    members.clear();
}

void Team::validateFile() {
    if (filename.substr(filename.find_last_of(".") + 1) != "txt") {
        throw FileLoadError(filename);
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw FileLoadError(filename);
    }

    std::string line;
    int lineNumber = 1;

    while (std::getline(file, line)) {
        auto fields = parseLine(line, lineNumber);
        validateLine(fields, lineNumber);
        lineNumber++;
    }
}

std::vector<std::string> Team::parseLine(const std::string& line, int lineNumber) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    
    while (std::getline(ss, field, ';')) {
        fields.push_back(field);
    }

    if (fields.size() != 4) {
        throw InvalidFormatError(lineNumber);
    }

    return fields;
}

void Team::validateLine(const std::vector<std::string>& fields, int lineNumber) {
    // Validate member type
    if (fields[0] != "Coach" && fields[0] != "Player") {
        throw InvalidTypeError(fields[0], lineNumber);
    }

    // Validate name
    if (fields[1].empty()) {
        throw EmptyNameError(lineNumber);
    }

    // Validate date
    validateDate(fields[2], lineNumber);

    // Validate additional field based on member type
    if (fields[0] == "Player") {
        try {
            int goals = std::stoi(fields[3]);
            if (goals < 0) {
                throw InvalidGoalsError(fields[3], lineNumber);
            }
        } catch (const std::invalid_argument&) {
            throw InvalidGoalsError(fields[3], lineNumber);
        } catch (const std::out_of_range&) {
            throw InvalidGoalsError(fields[3], lineNumber);
        }
    }
}

void Team::validateDate(const std::string& date, int lineNumber) {
    std::regex dateRegex("^([0-9]{2})\\.([0-9]{2})\\.([0-9]{4})$");
    if (!std::regex_match(date, dateRegex)) {
        throw InvalidDateError(date, lineNumber);
    }
}

void Team::validateType(const std::string& type) {
    if (type != "Player" && type != "Coach") {
        throw InvalidTypeError(type, 0);  // 0 it's user input line default
    }
}

void Team::validateName(const std::string& name) {
    if (name.empty()) {
        throw EmptyNameError(0);  // same line is 0 default
    }
    // we can also produce more checks here
}

/**
 * Validates a given string representing the number of goals a player has scored.
 * Checks that the string can be converted to an integer and that the number is not negative.
 * Throws an InvalidGoalsError if the string cannot be converted to an integer, or if the number is negative.
 * @param goalsStr a string representing the number of goals scored
 */
void Team::validateGoals(const std::string& goalsStr) {
    try {
        int goals = std::stoi(goalsStr);
        if (goals < 0) {
            throw InvalidGoalsError(goalsStr, 0);
        }
    } catch (const std::invalid_argument&) {
        throw InvalidGoalsError(goalsStr, 0);
    } catch (const std::out_of_range&) {
        throw InvalidGoalsError(goalsStr, 0);
    }
}

void Team::validateCategory(const std::string& category) {
    if (category.empty()) {
        throw TeamError("Category cannot be empty");
    }
    // some more checks can be added here also
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
    try {
        std::string type, name, birthdate, additional;
        
        // get annd validate type
        std::cout << "Enter member type (Player/Coach): ";
        std::getline(std::cin, type);
        validateType(type);
        
        // get and validate name
        std::cout << "Enter name: ";
        std::getline(std::cin, name);
        validateName(name);
        
        // gget and validate birthdate
        std::cout << "Enter birthdate (DD.MM.YYYY): ";
        std::getline(std::cin, birthdate);
        validateDate(birthdate, 0);  // 0 for line defauult line users input

        if (type == "Player") {
            std::string goalsStr;
            std::cout << "Enter number of goals in career: ";
            std::getline(std::cin, goalsStr);
            validateGoals(goalsStr);
            int goals = std::stoi(goalsStr);
            members.push_back(new Player(name, birthdate, goals));
        } else {  // type is Coach (already validated)
            std::cout << "Enter category: ";
            std::getline(std::cin, additional);
            validateCategory(additional);
            members.push_back(new Coach(name, birthdate, additional));
        }

        saveMembers();
        std::cout << "Team member added successfully!" << std::endl;
        
    } catch (const TeamError& e) {
        std::cout << "Error adding team member: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }
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

    auto compare_birthdate = [](const Player* a, const Player* b) {
        // 1900-based in std::tm
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

    // output
    std::cout << "\n--- Youngest and Oldest Players ---" << std::endl;
    
    // Youngest Player details
    std::cout << "Youngest Player:" << std::endl;
    std::cout << "Name: " << youngest->getName() << std::endl;
    
    char buffer[80];
    std::tm youngest_tm = youngest->getBirthdate();
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

Player* Team::selectPlayer() const {
    if (members.empty()) {
        std::cout << "No members in the team." << std::endl;
        return nullptr;
    }

    // Show available players
    std::cout << "\nAvailable players:" << std::endl;
    int playerCount = 0;
    for (const auto& member : members) {
        if (auto* player = dynamic_cast<Player*>(member)) {
            playerCount++;
            std::cout << player->getName() << " (Goals: " << player->getGoals() << ")" << std::endl;
        }
    }

    if (playerCount == 0) {
        std::cout << "No players available." << std::endl;
        return nullptr;
    }

    // Get player name
    std::string playerName;
    std::cout << "\nEnter player name to select: ";
    std::getline(std::cin, playerName);

    // Find and return the player
    for (auto* member : members) {
        if (auto* player = dynamic_cast<Player*>(member)) {
            if (player->getName() == playerName) {
                return player;
            }
        }
    }

    std::cout << "Player not found." << std::endl;
    return nullptr;
}