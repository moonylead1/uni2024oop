#ifndef BASICUSERDISPLAY_H
#define BASICUSERDISPLAY_H

#include "UserDisplayStrategy.h"

#include <iostream>

/*displays the basic info of the user as ID and status needed for admin usage*/
class BasicUserDisplay : public UserDisplayStrategy {
public:
    void display(const User& user) const override {
        std::cout << "------Basic User Display------ \n";
        std::cout << "ID: " << user.getId() << std::endl;
        std::cout << "Status: " << user.getStatus() << std::endl;
    }
};

#endif