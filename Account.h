#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Transaction.h"

using namespace std;

class Account
{
    string username;
    int accountNumber;
    string accountType;
    double balance;

    Account(string user, int accNum, string type, double bal)
        : username(user), accountNumber(accNum), accountType(type), balance(bal) {}

    string getUsername() const { return username; }
    int getAccountNumber() const { return accountNumber; }
    string getAccountType() const { return accountType; }
    double getBalance() const { return balance; }

    void deposit(double amount, string date) 
    {
        balance += amount;
        Transaction(accountNumber, amount, "Deposit", date).saveTransaction();
    }

    bool withdraw(double amount, string date)
    {
        if (amount > balance) return false;
        balance -= amount;
        Transaction(accountNumber, amount, "Withdrawal", date).saveTransaction();
        return true;
    }

    static vector<Account> loadAccounts(string targetUsername)
    {
        vector<Account> accounts;
        ifstream file("bank_data.txt");
        string line;

        while (getline(file, line)) {
            if (line == "[ACCOUNTS]") continue;
            stringstream ss(line);
            string username, accNum, type, bal;

            getline(ss, username, ',');
            getline(ss, accNum, ',');
            getline(ss, type, ',');
            getline(ss, bal, ',');

            if (username == targetUsername) 
                accounts.emplace_back(username, stoi(accNum), type, stod(bal));
        }
        file.close();
        return accounts;
    }

    void saveAccount() const 
    {
        ofstream file("bank_data.txt", ios::app);
        if (file.is_open()) {
            file << username << "," << accountNumber << "," << accountType << "," << balance << "\n";
            file.close();
        }
    }
};