#ifndef TRAINER_H
#define TRAINER_H

#include <string>
#include "Team.h"

class Trainer
{
private:
    std::string name;
public:
    Trainer(const std::string& name);
    std::string get_name() const;
    ~Trainer();
};

#endif



