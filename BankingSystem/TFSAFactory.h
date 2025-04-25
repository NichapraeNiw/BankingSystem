#pragma once
#include "AccountFactory.h"
#include "GIC12MonthDecorator.h"
#include "TFSA.h"
#include <iostream>
using namespace std;

class TFSAFactory : public AccountFactory
{
public:
    Account* createAccount(string username, double bal) override { return new GIC12MonthDecorator(new TFSA(username, bal)); }
    Account* createAccount(string username, double bal, string date) override { return new GIC12MonthDecorator(new TFSA(username, bal, date)); }
    Account* createAccount(string username, string accNum, double bal, string date) override { return new GIC12MonthDecorator(new TFSA(username, accNum, bal, date)); }
};