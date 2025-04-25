#pragma once
#include "AccountFactory.h"
#include "GIC100DayDecorator.h"
#include "FixedDeposit.h"
#include <iostream>
using namespace std;

class FixedDepositFactory : public AccountFactory
{
public:
    Account* createAccount(string username, double bal) override { return new GIC100DayDecorator(new FixedDeposit(username, bal)); }
    Account* createAccount(string username, double bal, string date) override { return new GIC100DayDecorator(new FixedDeposit(username, bal, date)); }
    Account* createAccount(string username, string accNum, double bal, string date) override { return new GIC100DayDecorator(new FixedDeposit(username, accNum, bal, date)); }
};