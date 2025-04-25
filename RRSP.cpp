#include "RRSP.h"

RRSP::RRSP(string username, double bal)
	: Account(username, "RRSP", bal)
{}

RRSP::RRSP(string username, double bal, string date)
	: Account(username, "RRSP", bal, date)
{}

RRSP::RRSP(string username, string accNum, double bal, string date)
	: Account(username, accNum, "RRSP", bal, date)
{}