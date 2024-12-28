#ifndef TEAM_H
#define TEAM_H

#include <fstream> // *modconcacs for file mod concurrent access 
//#include <thread> // *modconcacs for file mod concurrent access 
#include <chrono> // *modconcacs for file mod concurrent access
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

    static const int MAX_RETRIES = 5;
    
    bool acquireLock() const {
        std::string lockFile = filename + ".lock";
        int retries = 0;
        
        while (retries < MAX_RETRIES) {
            std::ifstream checkLock(lockFile.c_str());
            if (!checkLock.good()) {
                checkLock.close();
                std::ofstream lock(lockFile.c_str());
                if (lock.good()) {
                    lock.close();
                    return true;
                }
            }
            checkLock.close();
            
            // without using threads fuck this c11+
            for(int i = 0; i < 10000000; i++) {
                //  loop to create delay
            }
            
            retries++;
        }
        return false;
    }
    
    void releaseLock() const {
        std::string lockFile = filename + ".lock";
        std::remove(lockFile.c_str());
    }

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