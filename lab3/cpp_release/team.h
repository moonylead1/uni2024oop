#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "file_manager.h"
#include "team_member.h"


class Team {
private:
    std::vector<TeamMember*> members;
    std::string filename;

public:
    Team(const std::string& filename = "team_members.txt") : filename(filename) {
        load_members();
    }

    ~Team() {
        for (auto member : members) {
            delete member;
        }
    }

    void load_members() {
        members = file_manager.load_team_members(filename);
    }

    void save_members() {
        file_manager.save_team_members(members, filename);
    }

    void add_player(const std::string& name, const std::string& birthdate, int goals) {
        members.push_back(new Player(name, birthdate, goals));
        save_members();
    }

    void add_coach(const std::string& name, const std::string& birthdate, const std::string& category) {
        members.push_back(new Coach(name, birthdate, category));
        save_members();
    }

    void view_team() const {
        if (members.empty()) {
            std::cout << "Team is empty." << std::endl;
            return;
        }

        std::cout << "\n--- Team Members ---" << std::endl;
        for (const auto& member : members) {
            std::cout << "\nType: " << member->get_type() << std::endl;
            std::cout << "Name: " << member->get_name() << std::endl;
            
            char buffer[80];
            std::tm birthdate_tm = member->get_birthdate();
            std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", &birthdate_tm);
            std::cout << "Birthdate: " << buffer << std::endl;
            
            std::cout << "Age: " << member->get_age() << " years" << std::endl;

            if (auto* player = dynamic_cast<Player*>(member)) {
                std::cout << "Career Goals: " << player->get_goals() << std::endl;
            } else if (auto* coach = dynamic_cast<Coach*>(member)) {
                std::cout << "Category: " << coach->get_category() << std::endl;
            }
        }
    }

    void find_youngest_oldest_player() const {
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
                std::tm a_tm = a->get_birthdate();
                std::tm b_tm = b->get_birthdate();
                return std::mktime(&a_tm) > std::mktime(&b_tm);
            });

        auto oldest = *std::min_element(players.begin(), players.end(), 
            [](const Player* a, const Player* b) {
                std::tm a_tm = a->get_birthdate();
                std::tm b_tm = b->get_birthdate();
                return std::mktime(&a_tm) < std::mktime(&b_tm);
            });

        std::cout << "\n--- Youngest and Oldest Players ---" << std::endl;
        
        std::cout << "Youngest Player:" << std::endl;
        std::cout << "Name: " << youngest->get_name() << std::endl;
        
        char buffer[80];
        std::tm youngest_tm = youngest->get_birthdate();
        std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", &youngest_tm);
        std::cout << "Birthdate: " << buffer << std::endl;
        
        std::cout << "Age: " << youngest->get_age() << " years" << std::endl;
        std::cout << "Career Goals: " << youngest->get_goals() << std::endl;

        std::cout << "\nOldest Player:" << std::endl;
        std::cout << "Name: " << oldest->get_name() << std::endl;
        
        std::tm oldest_tm = oldest->get_birthdate();
        std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", &oldest_tm);
        std::cout << "Birthdate: " << buffer << std::endl;
        
        std::cout << "Age: " << oldest->get_age() << " years" << std::endl;
        std::cout << "Career Goals: " << oldest->get_goals() << std::endl;
    }

private:
    FileManager file_manager;
};

#endif // TEAM_H