#include "Team.h"
#include <stdexcept>

const Player* Team::get_youngest_player() const {
    if (players_.empty()) {
        throw std::runtime_error("Team has no players");
    }

    const Player* youngest = players_[0].get();
    for (const auto& player : players_) {
        if (player->get_age() < youngest->get_age()) {
            youngest = player.get();
        }
    }
    return youngest;
}

const Player* Team::get_oldest_player() const {
    if (players_.empty()) {
        throw std::runtime_error("Team has no players");
    }

    const Player* oldest = players_[0].get();
    for (const auto& player : players_) {
        if (player->get_age() > oldest->get_age()) {
            oldest = player.get();
        }
    }
    return oldest;
}

void Team::add_player(std::unique_ptr<Player> player) { //upd to uniqueptr 
    players_.push_back(std::move(player));
}

std::unique_ptr<Player> Team::remove_player(size_t index) { //changed to return uniqptr
    if (index >= players_.size()) {
        throw std::out_of_range("Player index out of range");
    }
    std::unique_ptr<Player> removed_player = std::move(players_[index]);
    players_.erase(players_.begin() + index);
    return removed_player;
}