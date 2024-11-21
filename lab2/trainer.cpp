#include "Trainer.h"
#include <string>

//default constructor
Trainer::Trainer(std::string name) : name(name) {}

/// default destructor
Trainer::~Trainer() {}

//basic getters
std::string Trainer::get_name() const {
    return name;
}