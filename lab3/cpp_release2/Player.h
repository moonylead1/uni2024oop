#ifndef PLAYER_H
#define PLAYER_H

#include "TeamMember.h"
#include <string>

class Player : public TeamMember {
private:
    int goals;

public:
    Player(const std::string& name, const std::string& birthdate, int goals);

    std::string getType() const override;
    int getGoals() const { return goals; };
    
    std::string getDetailsForSave() const override;
};

#endif // PLAYER_H