#pragma once
#include <iostream>
#include "Account.h"
using namespace std;

class Chequing : public Account
{
public:
	Chequing(string username, double bal);
	Chequing(string username, double bal, string date);
	Chequing(string username, string accNum, double bal, string date);

	void applyInterest() override {} // No interest for Chequing
};