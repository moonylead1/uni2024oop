#include "Trainer.h"
#include "Team.h"
#include <string>

//default constructor
Trainer::Trainer(const std::string& name) : name(name) {}

/// default destructor
Trainer::~Trainer() {}

//basic getters
std::string Trainer::get_name() const {
    return name;
}
