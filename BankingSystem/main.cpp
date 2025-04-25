#pragma once
#include <iostream>
#include "Bank.h"
#include "Chequing.h"
#include "SavingFactory.h"

using namespace std;
int main()
{
	Bank* bank = Bank::getInstance(); // Get the singleton instance
	bank->BankingConsole();

	Bank::destroyInstance(); // clean up

	return 0;
}