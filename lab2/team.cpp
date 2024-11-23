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
    for (auto* player : players) {
        delete player;
    }
    players.clear();
}

//basic getters
std::string Team::get_name() const {
    return name;
}

std::vector<Player*> Team::get_players() const {
    return players;
}

Trainer* Team::get_trainer() const {
    return trainer;
}

void Team::set_trainer(Trainer* trainer){
    this->trainer = trainer;
}