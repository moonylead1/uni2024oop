#include "Player.h"
#include <sstream>

Player::Player(const std::string& player) {
    std::istringstream iss(player);
    
    // Extract name and age from the input string
    if (!(iss >> name >> age)) {
        // Handle error if parsing fails
        name = "Unknown";
        age = 0;
    }
}

std::string Player::get_name() const {
    return name;
}

int Player::get_age() const {
    return age;
}