#pragma once
#include <iostream>
#include "Account.h"
using namespace std;

class RRSP : public Account
{
public:
	RRSP(string username, double bal);
	RRSP(string username, double bal, string date);
	RRSP(string username, string accNum, double bal, string date);

	void applyInterest() override {} // No interest for RRSP
};