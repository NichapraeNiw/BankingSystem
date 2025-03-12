#include <fstream>
#include <vector>
#include <sstream>
#include "Transaction.h"

Transaction::Transaction(int accNum, double amt, string t, string d)
	: accountNumber(accNum), amount(amt), type(t), date(d)
{}

vector<Transaction> Transaction::loadTransactions(int targetAccountNumber)
{
    vector<Transaction> transactions;
    ifstream file("bank_data.txt");
    string line;

    while (getline(file, line))
    {
        if (line == "[TRANSACTIONS]") continue;
        stringstream ss(line);
        string accNum, amt, type, date;

        getline(ss, accNum, ',');
        getline(ss, amt, ',');
        getline(ss, type, ',');
        getline(ss, date, ',');

        if (stoi(accNum) == targetAccountNumber)
            transactions.emplace_back(stoi(accNum), stod(amt), type, date);
    }

    file.close();
    return transactions;
}

void Transaction::saveTransaction() const
{
    ofstream file("bank_data.txt", ios::app);
    if (file.is_open())
    {
        file << accountNumber << "," << amount << "," << type << "," << date << "\n";
        file.close();
    }
}

void Transaction::displayTransaction() const
{
    cout << accountNumber << "," << amount << "," << type << "," << date << "\n";
}