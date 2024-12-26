#ifndef MENU_H
#define MENU_H

#include "Team.h"

class Menu {
private:
    Team team;
    std::vector<Player*> onDutyPlayers;
public:
    //void displayMainMenu();
    void run();
    void showOnDutyPlayers() const;

private:
    void displayMenuOptions();
    void processUserChoice(int choice);
};

#endif // MENU_H