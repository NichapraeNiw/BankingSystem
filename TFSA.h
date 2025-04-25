#pragma once
#include <iostream>
#include "Account.h"
using namespace std;

class TFSA : public Account
{
public:
	TFSA(string username, double bal);
	TFSA(string username, double bal, string date);
	TFSA(string username, string accNum, double bal, string date);

	void applyInterest() override {}  // Handled by Decorator
};