#ifndef SEARCHBYSTATUS_H
#define SEARCHBYSTATUS_H

#include "UserSearchStrategy.h"

#include <string>

class SearchByStatus : public UserSearchStrategy {
public:
    bool matches(const User& user, const std::string& searchTerm) const override {
        return user.getStatus().find(searchTerm) != std::string::npos;
    }
}; 

#endif