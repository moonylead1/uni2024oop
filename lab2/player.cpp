#include "Player.h"

Player::Player(const std::string& name, int age, const std::string& position, int touchdowns, Team team, bool ingame) : name(name), age(age), position(position), touchdowns(touchdowns), team(team) {
}

Player::~Player() {}

std::string Player::get_name() const {
    return name;
}

int Player::get_age() const {
    return age;
}

std::string Player::get_position() const {
    return position;
}

int Player::get_touchdowns() const {
    return touchdowns;
}

Team Player::get_team() const {
    return team;
}

bool Player::get_ingame() const {
    return ingame;
}

bool Player::set_ingame(bool ingame) {
    this->ingame = ingame;
    return ingame;
}