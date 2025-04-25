#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include "Customer.h"
using namespace std;

class Bank
{
private:
	static Bank* instance; // Singleton instance
	Bank() {} // Private constructor
	~Bank() {} // Private deconstructor

public:
	// Prevent copying and assignment
	Bank(const Bank&) = delete;
	Bank& operator=(const Bank&) = delete;

	// Static method to get the singleton instance
	static Bank* getInstance();
	static void destroyInstance();

	// functions for displaying
	Customer* login();
	Customer* signUp();
	void BankingConsole();
	void BankingOption(Customer* cus);
	void createAccount(Customer* cus); // option 1
	void deleteAccount(Customer* cus); // option 2
	void deposit(Customer* cus); // option 3
	void withdraw(Customer* cus); // option 4
	void transfer(Customer* cus); // option 5
	void displayYourAccount(Customer* cus); // option 6
};