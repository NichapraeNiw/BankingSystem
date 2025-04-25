#include "Chequing.h"

Chequing::Chequing(string username, double bal)
	: Account(username, "Chequing", bal)
{}

Chequing::Chequing(string username, double bal, string date) // if we want to create it with date
	: Account(username, "Chequing", bal, date)
{}

Chequing::Chequing(string username, string accNum, double bal, string date)
	: Account(username, accNum, "Chequing", bal, date)
{}