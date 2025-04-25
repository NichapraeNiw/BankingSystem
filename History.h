#pragma once
#include "Utilities.h"
using namespace std;

class History
{
protected:
    string accountNumber;
    double amount;
    string type;
    string date;

public:
    History(string accNum, double amt, string t);
    string getAccountNumber() const { return accountNumber; }
    double getAmount() const { return amount; }
    string getType() const { return type; }
    string getDate() const { return date; }

    static void logEvent(string accNum, double amt, string type, string date);
    static void displayHistoryLogFromAccountNumber(string accountNumber);
    static string getLastInterestDate(string accountNumber);
};