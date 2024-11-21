#include "Player.h"
#include "Trainer.h"
#include <vector>
#include <string>


class Team
{
private:
    std::string name;
    std::vector<Player> players;
    Trainer trainer;
public:
    Team(/* args */);
    ~Team();
};

Team::Team(/* args */)
{
}

Team::~Team()
{
}
