#ifndef USERDISPLAYSTRATEGY_H
#define USERDISPLAYSTRATEGY_H
#include "User.h"

class UserDisplayStrategy
{
public:
    virtual void display(const User& user) const = 0;
    virtual ~UserDisplayStrategy() = default;
};

#endif