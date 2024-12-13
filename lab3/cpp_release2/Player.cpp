#include "Player.h"
#include <sstream>
#include <iomanip>

Player::Player(const std::string& name, const std::string& birthdate, int goals)
    : TeamMember(name, birthdate), goals(goals) {}

std::string Player::getType() const {
    return "Player";
}

int Player::getGoals() const {
    return goals;
}

std::string Player::getDetailsForSave() const {
    std::ostringstream oss;
    std::tm birthdate_copy = TeamMember::getBirthdate(); // Create a copy
    oss << "Player;" 
        << getName() << ";" 
        << std::put_time(&birthdate_copy, "%d.%m.%Y") << ";" 
        << getGoals();
    return oss.str();
}