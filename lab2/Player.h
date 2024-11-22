#ifndef PLAYER_H
#define PLAYER_H
#include "Team.h"
#include <string>


class Player
{
private:
    std::string name;
    int age;
    std::string position;
    int touchdowns;
    Team team; // this is the time we move to team function and play with team+vector for players INSIDE team
    bool ingame = false;
public:
    Player(const std::string& name, int age, const std::string& position, int touchdowns, Team team, bool ingame);
    ~Player();

    std::string get_name() const;
    int get_age() const;
    std::string get_position() const;
    int get_touchdowns() const;
    Team get_team() const;
    bool get_ingame() const;
    bool set_ingame(bool ingame);

};



#endif