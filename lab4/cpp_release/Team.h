#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>
#include "Player.h"
#include "Coach.h"
#include "TeamMember.h"
#include "Exceptions.h"

class Team {
private:
    std::vector<TeamMember*> members;
    std::string filename;

    void validateLine(const std::vector<std::string>& fields, int lineNumber);
    void validateDate(const std::string& date, int lineNumber);
    std::vector<std::string> parseLine(const std::string& line, int lineNumber);

    void validateType(const std::string& type);
    void validateName(const std::string& name);
    void validateGoals(const std::string& goalsStr);
    void validateCategory(const std::string& category);


public:
    explicit Team(const std::string& filename = "team_members.txt");
    ~Team();

    void loadMembers();
    void saveMembers();
    void addMember();
    void viewTeam();
    void findYoungestOldestPlayer();
    void validateFile();
    Player* selectPlayer() const;
};

#endif // TEAM_H