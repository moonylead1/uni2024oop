#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>
#include "Player.h"
#include "Coach.h"
#include "TeamMember.h"

class Team {
private:
    std::vector<TeamMember*> members;
    std::string filename;

public:
    Team(const std::string& filename = "team_members.txt");
    ~Team();

    void loadMembers();
    void saveMembers();
    void addMember();
    void viewTeam();
    void findYoungestOldestPlayer();
};

#endif // TEAM_H