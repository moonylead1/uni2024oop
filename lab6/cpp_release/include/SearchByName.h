#ifndef SEARCHBYNAME_H
#define SEARCHBYNAME_H

#include "UserSearchStrategy.h"

#include <string>

class SearchByName : public UserSearchStrategy {
public:
    bool matches(const User& user, const std::string& searchTerm) const override {
        return user.get_name().find(searchTerm) != std::string::npos;
    }
}; 

#endif