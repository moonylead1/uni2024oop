#ifndef USERSEARCHSTRATEGY_H
#define USERSEARCHSTRATEGY_H

#include "User.h"

#include <string>

class UserSearchStrategy {
public:
    virtual bool matches(const User& user, const std::string& searchTerm) const = 0;
    virtual ~UserSearchStrategy() = default;
};

#endif // USERSEARCHSTRATEGY_H