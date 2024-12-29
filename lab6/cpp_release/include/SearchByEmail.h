#ifndef SEARCHBYEMAIL_H
#define SEARCHBYEMAIL_H

#include "UserSearchStrategy.h"

#include <string>

class SearchByEmail : public UserSearchStrategy {
public:
    bool matches(const User& user, const std::string& searchTerm) const override {
        return user.get_email().find(searchTerm) != std::string::npos;
    }
}; 

#endif