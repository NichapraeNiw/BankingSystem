#pragma once
#include <iostream>
#include "Account.h"
using namespace std;

class FixedDeposit : public Account
{
public:
	FixedDeposit(string username, double bal);
	FixedDeposit(string username, double bal, string date);
	FixedDeposit(string username, string accNum, double bal, string date);

	void applyInterest() override {}  // Handled by Decorator
};