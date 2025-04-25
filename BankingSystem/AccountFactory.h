#pragma once
#include "Account.h"
#include <iostream>
using namespace std;

class AccountFactory
{
public:
	virtual Account* createAccount(string username, double bal) = 0;
	virtual Account* createAccount(string username, double bal, string date) = 0; // Employer part, if they have specific date to implement
	virtual Account* createAccount(string username, string accNum, double bal, string date) = 0;

	virtual ~AccountFactory() {}
};