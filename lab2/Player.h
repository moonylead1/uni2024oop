#include <string>

class Player
{
private:
    std::string name;
    int age;
    std::string position;
    int touchdowns;
    Team* team; // this is the time we move to team function and play with team+vector for players INSIDE team
public:
    Player(const std::string& player);
    ~Player();

    std::string get_name() const;
    int get_age() const;


};

Player::Player(const std::string& player)
{
}

Player::~Player()
{
}
