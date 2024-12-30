#ifndef DETAILEDUSERDISPLAY_H
#define DETAILEDUSERDISPLAY_H

#include "UserDisplayStrategy.h"

#include <iostream>

class DetailedUserDisplay : public UserDisplayStrategy {
public:
    void display(const User& user) const override {
        std::cout << "------Detailed User Display------ \n";
        std::cout << "ID: " << user.getId() << std::endl;
        std::cout << "Status: " << user.getStatus() << std::endl;
        std::cout << "Name: " << user.getName() << std::endl;
        std::cout << "Email: " << user.getEmail() << std::endl;
        std::cout << "Role: " << user.getRole() << std::endl;
    }
};

#endif