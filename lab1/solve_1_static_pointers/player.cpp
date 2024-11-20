#include "Player.h"
#include <sstream>

Player::Player(const std::string& player) {
    std::istringstream iss(player);
    
    // Extract name and age from the input string found the better implementation thru StackEx by sstream
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