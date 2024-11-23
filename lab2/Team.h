#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>
#include <algorithm>

class Player;
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
    std::vector<Player*>& get_players();
    Trainer* get_trainer() const;

    //setters
    void set_trainer(Trainer* new_trainer) { trainer = new_trainer; }
    void add_player(Player* player){
        if (player) {
            players.push_back(player);
        }
    }

    void remove_player(Player* player) {
        auto it = std::find(players.begin(), players.end(), player);
        if (it != players.end()) {
            players.erase(it);
        }
    }
    
};

#endif