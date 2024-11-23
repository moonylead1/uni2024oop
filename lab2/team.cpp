#include "Team.h"
#include <string>

//default constructor
Team::Team(std::string name, std::vector<Player*> players, Trainer* trainer) :
    name(name),
    players(players),
    trainer(trainer) {
}

//default destructor
Team::~Team() {
    // clear the vector but not obj
    players.clear();
    trainer = nullptr;
}

//basic getters
std::string Team::get_name() const {
    return name;
}

std::vector<Player*>& Team::get_players() {
    return players;
}

Trainer* Team::get_trainer() const {
    return trainer;
}


