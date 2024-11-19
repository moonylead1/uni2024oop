#include "Team.h"
#include <stdexcept>

Player Team::get_youngest_player() const {
    if (players_.empty()) {
        // case when the team has no players
        throw std::runtime_error("Team has no players");
    }

    Player youngest = players_[0];
    for (const auto& player : players_) {
        if (player.get_age() < youngest.get_age()) {
            youngest = player;
        }
    }
    return youngest;
}

Player Team::get_oldest_player() const {
    if (players_.empty()) {
        // case when the team has no players
        throw std::runtime_error("Team has no players");
    }

    Player oldest = players_[0];
    for (const auto& player : players_) {
        if (player.get_age() > oldest.get_age()) {
            oldest = player;
        }
    }
    return oldest;
}

void Team::add_player(const Player& player) {
    players_.push_back(player);
}

void Team::remove_player(size_t index) {
    if (index >= players_.size()) {
        throw std::out_of_range("Player index out of range");
    }
    players_.erase(players_.begin() + index);
}
