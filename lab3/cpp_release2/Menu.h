#ifndef MENU_H
#define MENU_H

#include "Team.h"

class Menu {
private:
    Team team;

public:
    //void displayMainMenu();
    void run();

private:
    void displayMenuOptions();
    void processUserChoice(int choice);
};

#endif // MENU_H