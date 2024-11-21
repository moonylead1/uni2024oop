#include "Team.h"
#include <string>

//default constructor
Team::Team(std::string name, std::vector<Player> players, Trainer trainer) : name(""), players(std::vector<Player>()), trainer(Trainer("")) {}

//default destructor
Team::~Team() {

}

//basic getters
std::string Team::get_name() const {
    return name;
}

std::vector<Player> Team::get_players() const {
    return players;
}

Trainer Team::get_trainer() const {
    return trainer;
}