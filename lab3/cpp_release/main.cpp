#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <iomanip>

// Base class for team members
class TeamMember {
protected:
    std::string name;
    std::tm birthdate;

public:
    TeamMember(const std::string& name, const std::string& birthdateStr) {
        this->name = name;
        
        std::istringstream ss(birthdateStr);
        ss >> std::get_time(&birthdate, "%d.%m.%Y");
    }

    // Pure virtual method to get member type
    virtual std::string getType() const = 0;
    
    // Calculate age based on current date
    int getAge() const {
        std::time_t now = std::time(0);
        std::tm* today = std::localtime(&now);
        
        int age = today->tm_year + 1900 - (birthdate.tm_year + 1900);
        if (today->tm_mon < birthdate.tm_mon || 
            (today->tm_mon == birthdate.tm_mon && today->tm_mday < birthdate.tm_mday)) {
            age--;
        }
        
        return age;
    }

    std::string getName() const { return name; }
    std::tm getBirthdate() const { return birthdate; }
    virtual std::string getDetailsForSave() const = 0;
    virtual ~TeamMember() = default;
};

// Player class derived from TeamMember
class Player : public TeamMember {
private:
    int goals;

public:
    Player(const std::string& name, const std::string& birthdate, int goals) 
        : TeamMember(name, birthdate), goals(goals) {}

    std::string getType() const override { return "Player"; }
    int getGoals() const { return goals; }
    
    // Format details for saving to file
    std::string getDetailsForSave() const override {
        return "Player;" + name + ";" + 
               std::to_string(birthdate.tm_mday) + "." + 
               std::to_string(birthdate.tm_mon + 1) + "." + 
               std::to_string(birthdate.tm_year + 1900) + ";" + 
               std::to_string(goals);
    }
};

// Coach class derived from TeamMember
class Coach : public TeamMember {
private:
    std::string category;

public:
    Coach(const std::string& name, const std::string& birthdate, const std::string& category) 
        : TeamMember(name, birthdate), category(category) {}

    std::string getType() const override { return "Coach"; }
    std::string getCategory() const { return category; }
    
    // Format details for saving to file
    std::string getDetailsForSave() const override {
        return "Coach;" + name + ";" + 
               std::to_string(birthdate.tm_mday) + "." + 
               std::to_string(birthdate.tm_mon + 1) + "." + 
               std::to_string(birthdate.tm_year + 1900) + ";" + 
               category;
    }
};

// Team management class
class Team {
private:
    std::vector<TeamMember*> members;
    std::string filename;

public:
    Team(const std::string& filename = "team_members.txt") : filename(filename) {
        loadMembers();
    }

    // Destructor to free dynamically allocated memory
    ~Team() {
        for (auto member : members) {
            delete member;
        }
    }

    // Load team members from file
    void loadMembers() {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string type, name, birthdateStr, additional;
            
            std::getline(ss, type, ';');
            std::getline(ss, name, ';');
            std::getline(ss, birthdateStr, ';');
            std::getline(ss, additional);

            if (type == "Player") {
                members.push_back(new Player(name, birthdateStr, std::stoi(additional)));
            } else if (type == "Coach") {
                members.push_back(new Coach(name, birthdateStr, additional));
            }
        }
    }

    // Save team members to file
    void saveMembers() {
        std::ofstream file(filename);
        for (const auto& member : members) {
            file << member->getDetailsForSave() << std::endl;
        }
    }

    // Add a new team member
    void addMember() {
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

    // View all team members
    void viewTeam() {
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

    // Find youngest and oldest players
    void findYoungestOldestPlayer() {
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

        auto youngest = *std::max_element(players.begin(), players.end(), 
            [](const Player* a, const Player* b) {
                std::tm a_tm = a->getBirthdate();
                std::tm b_tm = b->getBirthdate();
                return std::mktime(&a_tm) > std::mktime(&b_tm);
            });

        auto oldest = *std::min_element(players.begin(), players.end(), 
            [](const Player* a, const Player* b) {
                std::tm a_tm = a->getBirthdate();
                std::tm b_tm = b->getBirthdate();
                return std::mktime(&a_tm) < std::mktime(&b_tm);
            });

        std::cout << "\n--- Youngest and Oldest Players ---" << std::endl;
        
        std::cout << "Youngest Player:" << std::endl;
        std::cout << "Name: " << youngest->getName() << std::endl;
        
        char buffer[80];
        std::tm youngest_tm = youngest->getBirthdate();
        std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", &youngest_tm);
        std::cout << "Birthdate: " << buffer << std::endl;
        
        std::cout << "Age: " << youngest->getAge() << " years" << std::endl;
        std::cout << "Career Goals: " << youngest->getGoals() << std::endl;

        std::cout << "\nOldest Player:" << std::endl;
        std::cout << "Name: " << oldest->getName() << std::endl;
        
        std::tm oldest_tm = oldest->getBirthdate();
        std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", &oldest_tm);
        std::cout << "Birthdate: " << buffer << std::endl;
        
        std::cout << "Age: " << oldest->getAge() << " years" << std::endl;
        std::cout << "Career Goals: " << oldest->getGoals() << std::endl;
    }
};

// Display main menu
void displayMenu() {
    std::cout << "\n--- Team Management System ---" << std::endl;
    std::cout << "1. Add Team Member" << std::endl;
    std::cout << "2. View Team Members" << std::endl;
    std::cout << "3. Find Youngest and Oldest Players" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

// Main program
int main() {
    Team team;
    int choice;

    while (true) {
        displayMenu();
        std::cout << "Select an option: ";
        std::cin >> choice;
        std::cin.ignore();

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
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}