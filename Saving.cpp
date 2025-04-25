#include "Saving.h"

Saving::Saving(string username, double bal)
	: Account(username, "Saving", bal)
{}

Saving::Saving(string username, double bal, string date)
	: Account(username, "Saving", bal, date)
{}

Saving::Saving(string username, string accNum, double bal, string date)
	: Account(username, accNum, "Saving", bal, date)
{}