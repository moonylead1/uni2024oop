#ifndef TEAM_H
#define TEAM_H

#include "Trainer.h"
#include "Player.h"
#include <vector>
#include <string>


class Team
{
private:
    std::string name;
    std::vector<Player> players;
    Trainer trainer;
public:
    Team(std::string name, std::vector<Player> players, Trainer trainer);
    std::string Team::get_name() const;
    std::vector<Player> Team::get_players() const;
    Trainer Team::get_trainer() const;
    ~Team();
};

#endif