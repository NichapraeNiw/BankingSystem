#include "FixedDeposit.h"

FixedDeposit::FixedDeposit(string username, double bal)
	: Account(username, "FixedDeposit", bal)
{}

FixedDeposit::FixedDeposit(string username, double bal, string date)
	: Account(username, "FixedDeposit", bal, date)
{}

FixedDeposit::FixedDeposit(string username, string accNum, double bal, string date)
	: Account(username, accNum, "FixedDeposit", bal, date)
{}