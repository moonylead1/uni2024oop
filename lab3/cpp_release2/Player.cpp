#include "Player.h"

Player::Player(const std::string& name, const std::string& birthdate, int goals)
    : TeamMember(name, birthdate), goals(goals) {}

int Player::getGoals() const {
    return goals;
}