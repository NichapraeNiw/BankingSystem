#include "TFSA.h"

TFSA::TFSA(string username, double bal)
	: Account(username, "TFSA", bal)
{}

TFSA::TFSA(string username, double bal, string date)
	: Account(username, "TFSA", bal, date)
{}

TFSA::TFSA(string username, string accNum, double bal, string date)
	: Account(username, accNum, "TFSA", bal, date)
{}