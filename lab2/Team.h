#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include <vector>
#include <string>

class Trainer;

class Team
{
private:
    std::string name;
    std::vector<Player*> players;
    Trainer* trainer;
public:
    Team(std::string name, std::vector<Player* > players = {}, Trainer* trainer = nullptr);
    ~Team();
    
    std::string get_name() const;
    std::vector<Player*> get_players() const;
    Trainer* get_trainer() const;
    void set_trainer(Trainer* trainer);
    
};

#endif