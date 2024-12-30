#ifndef SEARCHBYID_H
#define SEARCHBYID_H

#include "UserSearchStrategy.h"

#include <string>

class SearchById : public UserSearchStrategy {
public:
    bool matches(const User& user, const std::string& searchTerm) const override {
        return user.getId() == searchTerm;
    }
}; 

#endif