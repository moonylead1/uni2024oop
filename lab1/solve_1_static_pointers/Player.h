#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(const std::string& player);
    std::string get_name() const;
    int get_age() const;

private:
    std::string name;
    int age;
};

#endif