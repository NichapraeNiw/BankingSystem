#pragma once
#include "AccountFactory.h"
#include "SavingInterestDecorator.h"
#include "Saving.h"
#include <iostream>
using namespace std;

class SavingFactory : public AccountFactory
{
public:
    Account* createAccount(string username, double bal) override { return new SavingInterestDecorator(new Saving(username, bal)); }
    Account* createAccount(string username, double bal, string date) override { return new SavingInterestDecorator(new Saving(username, bal, date)); }
    Account* createAccount(string username, string accNum, double bal, string date) override { return new SavingInterestDecorator(new Saving(username, accNum, bal, date)); }
};