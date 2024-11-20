#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include <vector>
#include <memory> //for uniq ptr
#include <stdexcept>

class Team {
public:
    Team(const std::string& name) : name_(name) {}
    // we do not more need destructor as uniqptr handle memory clean up automatically
    std::vector<std::unique_ptr<Player>>& get_players() { return players_; } //changed std::vector<Player*> to std::vector<std::unique_ptr<Player>>
    const std::vector<std::unique_ptr<Player>>& get_players() const { return players_; }
    std::string get_name() const { return name_; }
    const Player* get_youngest_player() const;
    const Player* get_oldest_player() const;
    void add_player(std::unique_ptr<Player> player);
    std::unique_ptr<Player> remove_player(size_t index);
    
    const Player* get_player(size_t index) const {
        if (index >= players_.size()) {
            throw std::out_of_range("Player index out of range");
        }
        return players_[index].get();
    }

    size_t size() const { return players_.size(); }

private:
    std::string name_;
    std::vector<std::unique_ptr<Player>> players_;
};

#endif