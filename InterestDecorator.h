#pragma once
#include "Account.h"
#include <iostream>
using namespace std;

class InterestDecorator : public Account
{
protected:
    Account* decoratedAccount;

public:
    InterestDecorator(Account* account);

    virtual void applyInterest() = 0;  // Force subclasses to define interest logic

    void displayAccountDetail() const override;
};