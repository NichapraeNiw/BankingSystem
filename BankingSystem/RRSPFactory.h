#pragma once
#include "AccountFactory.h"
#include "RRSP.h"
#include <iostream>
using namespace std;

class RRSPFactory : public AccountFactory
{
public:
    Account* createAccount(string username, double bal) override { return new RRSP(username, bal); }
    Account* createAccount(string username, double bal, string date) override { return new RRSP(username, bal, date); }
    Account* createAccount(string username, string accNum, double bal, string date) override { return new RRSP(username, accNum, bal, date); }
};