#include "Player.h"

Player::Player(const std::string& name, int age, const std::string& position, int touchdowns, Team* team, bool ingame) :
    name(name),
    age(age),
    position(position),
    touchdowns(touchdowns),
    team(team),
    ingame(ingame) {
}

Player::~Player() {}

const std::string &Player::get_name() const {
    return name;
}

int Player::get_age() const {
    return age;
}

const std::string &Player::get_position() const {
    return position;
}

int Player::get_touchdowns() const {
    return touchdowns;
}

Team* Player::get_team() const {
    return team;
}

bool Player::get_ingame() const {
    return ingame;
}

void Player::set_ingame(bool ingame) {
    this->ingame = ingame;
}

void Player::set_team(Team* team) {
    this->team = team;
}
