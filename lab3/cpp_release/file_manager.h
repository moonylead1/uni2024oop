#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <string>
#include "team_member.h"

class FileManager {
public:
    std::vector<TeamMember*> load_team_members(const std::string& filename) {
        std::vector<TeamMember*> members;

        std::ifstream file(filename);
        if (!file.is_open()) {
            return members;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string type, name, birthdateStr, additional;

            std::getline(ss, type, ';');
            std::getline(ss, name, ';');
            std::getline(ss, birthdateStr, ';');
            std::getline(ss, additional);

            if (type == "Player") {
                int goals = std::stoi(additional);
                members.push_back(new Player(name, birthdateStr, goals));
            } else if (type == "Coach") {
                members.push_back(new Coach(name, birthdateStr, additional));
            }
        }

        file.close();
        return members;
    }

    void save_team_members(const std::vector<TeamMember*>& members, const std::string& filename) {
        std::ofstream file(filename);

        for (const auto& member : members) {
            file << member->get_details_for_save() << std::endl;
        }

        file.close();
    }
};

#endif // FILE_MANAGER_H