#pragma once
#include <iostream>
#include "Account.h"

using namespace std;

class Saving : public Account
{
public:
	Saving(string username, double bal);
	Saving(string username, double bal, string date);
	Saving(string username, string accNum, double bal, string date);

	void applyInterest() override {}  // Handled by Decorator
};