#ifndef DETAILEDUSERDISPLAY_H
#define DETAILEDUSERDISPLAY_H

#include "UserDisplayStrategy.h"

#include <iostream>

class DetailedUserDisplay : public UserDisplayStrategy {
public:
    void display(const User& user) const override {
        std::cout << "------Detailed User Display------ \n";
        std::cout << "ID: " << user.get_id() << std::endl;
        std::cout << "Status: " << user.get_status() << std::endl;
        std::cout << "Name: " << user.get_name() << std::endl;
        std::cout << "Email: " << user.get_email() << std::endl;
        std::cout << "Role: " << user.get_role() << std::endl;
    }
};

#endif