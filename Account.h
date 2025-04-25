#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Account
{
protected:
	string username;
	string accountNumber;
	string accountType;
	double balance;
	string creationDate;

public:
	Account(string username, string accType, double bal); // create account with today date + save to file
	Account(string username, string accType, double bal, string date); // create account with specific date + save ti file
	Account(string username, string accNum, string accType, double bal, string date); // pull account from file and store in the program
	virtual ~Account() {}

	// getters
	string getUsername() const { return username; }
	string getAccountNumber() const { return accountNumber; }
	string getAccountType() const { return accountType; }
	double getBalance() const { return balance; }
	string getCreationDate() const { return creationDate; }

	// functions
	bool deposit(double amount);
	bool depositInterest(double amount);
	bool withdraw(double amount);
	bool transfer(double amount, Account* toAccount);
	void updateAccountBalance(double newBalance) const;
	virtual void applyInterest() = 0;  // Interest must be applied via decorator
	virtual void displayAccountDetail() const;
	static vector<Account*> findAccountsByUsername(const string& username);
};