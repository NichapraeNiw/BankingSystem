#pragma once
#include "AccountFactory.h"
#include "Chequing.h"
#include <iostream>
using namespace std;

class ChequingFactory : public AccountFactory
{
public:
    Account* createAccount(string username, double bal) override { return new Chequing(username, bal); }
    Account* createAccount(string username, double bal, string date) override { return new Chequing(username, bal, date); }
    Account* createAccount(string username, string accNum, double bal, string date) override { return new Chequing(username, accNum, bal, date); }
};