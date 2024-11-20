#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include <vector>
#include <stdexcept>

class Team {
public:
    Team(const std::string& name) : name_(name) {}
    ~Team(); // destructor 

    std::vector<Player*> get_players() const { return players_; }
    std::string get_name() const { return name_; }
    Player* get_youngest_player() const;
    Player* get_oldest_player() const;
    void add_player(Player* player);
    void remove_player(size_t index);
    
    const Player* get_player(size_t index) const {
        if (index >= players_.size()) {
            throw std::out_of_range("Player index out of range");
        }
        return players_[index];
    }

    size_t size() const { return players_.size(); }



private:
    std::string name_;
    std::vector<Player*> players_; //vector of pointers
};

#endif