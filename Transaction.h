#pragma once
#include <iostream>

using namespace std;

class Transaction 
{
private:
    int accountNumber;
    double amount;
    string type;
    string date;

public:
    Transaction(int accNum, double amt, string t, string d);
    int getAccountNumber() const { return accountNumber; }
    double getAmount() const { return amount; }
    string getType() const { return type; }
    string getDate() const { return date; }

    // This function static because we can fetch transaction history without needing to create a Transaction object
    static vector<Transaction> loadTransactions(int targetAccountNumber);
    void saveTransaction() const;
    void displayTransaction() const;
};
