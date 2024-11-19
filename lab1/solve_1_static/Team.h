#include "Player.h"
#include <vector>
#include <stdexcept>

class Team {
public:
    Team(const std::string& name, const std::vector<Player>& players) : name_(name), players_(players) {}
    std::vector<Player> get_players() const { return players_; }
    std::string get_name() const { return name_; }
    Player get_youngest_player() const;
    Player get_oldest_player() const;
    void add_player(const Player& player);
    void remove_player(size_t index);
    
    const Player& get_player(size_t index) const {
        if (index >= players_.size()) {
            throw std::out_of_range("Player index out of range");
        }
        return players_[index];
    }

    size_t size() const { return players_.size(); }


private:
    std::string name_;
    std::vector<Player> players_;
};