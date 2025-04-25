#include "Account.h"
#include "Utilities.h"
#include "History.h"
#include "SavingFactory.h"
#include "ChequingFactory.h"
#include "FixedDepositFactory.h"
#include "TFSAFactory.h"
#include "RRSPFactory.h"
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
#include <algorithm>

Account::Account(string username, string accType, double bal)
	: username(username), accountType(accType), balance(bal)
{
    this->accountNumber = Utilities::generateUniqueAccountNumber();
	this->creationDate = Utilities::getTodayString();

    // add new account to file
    ofstream file("Account.txt", ios::app);
    file << username << "," << accountNumber << "," << accountType << "," << balance << "," << creationDate << "\n";
    file.close();

    // update in history
    History::logEvent(accountNumber, balance, "AccountCreated", creationDate);
}

Account::Account(string username, string accType, double bal, string date)
    :username(username), accountType(accType), balance(bal), creationDate(date)
{
    this->accountNumber = Utilities::generateUniqueAccountNumber();

    // add new account to file
    ofstream file("Account.txt", ios::app);
    file << username << "," << accountNumber << "," << accountType << "," << balance << "," << creationDate << "\n";
    file.close();

    // update in history
    History::logEvent(accountNumber, balance, "AccountCreated", creationDate);
}

Account::Account(string username, string accNum, string accType, double bal, string date)
    : username(username), accountNumber(accNum), accountType(accType), balance(bal), creationDate(date)
{}

bool Account::deposit(double amount)
{
    if (amount > 0)
    {
        double newBalance;
        newBalance = balance += amount;
        cout << accountType << " Account: Deposited $" << amount << endl;
        History::logEvent(accountNumber, amount, "Deposit", Utilities::getTodayString());
        updateAccountBalance(newBalance);
        return true;
    }
    cout << "Invalid Deposit Amount.\n";
    return false;
}

bool Account::depositInterest(double amount)
{
    if (amount > 0)
    {
        double newBalance;
        newBalance = balance += amount;
        History::logEvent(accountNumber, amount, "Interest", Utilities::getTodayString());
        updateAccountBalance(newBalance);
        return true;
    }
    cout << "Account Has No Balance To Apply Interest.\n";
    return false;
}

bool Account::withdraw(double amount)
{
    if (amount > 0 && balance >= amount)
    {
        double newBalance;
        newBalance = balance -= amount;
        cout << accountType << " Account: Withdrawn $" << amount << endl;
        History::logEvent(accountNumber, amount, "Withdraw", Utilities::getTodayString());
        updateAccountBalance(newBalance);
        return true;
    }
    cout << "Insufficient funds or invalid amount.\n";
    return false;
}

bool Account::transfer(double amount, Account* toAccount)
{
    if (withdraw(amount))
    {
        cout << endl;
        toAccount->deposit(amount);
        cout << "\nTransferred $" << amount << " to " << toAccount->accountType << " Account.\n";
        return true;
    }
    return false;
}

void Account::displayAccountDetail() const
{
    ifstream file("Account.txt");
    string line;
    int accountExist = 0;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        string user, accNum, type, bal, date;
        getline(ss, user, ',');
        getline(ss, accNum, ',');
        getline(ss, type, ',');
        getline(ss, bal, ',');
        getline(ss, date, ',');

        if (Utilities::toLowerCase(user) == Utilities::toLowerCase(this->getUsername()) &&
            Utilities::toLowerCase(type) == Utilities::toLowerCase(this->getAccountType()))
        {
            cout << "\n====== Display Account ======" << endl;
            cout << "Username: " << user << endl;
            cout << "Account Number: " << accNum << endl;
            cout << "Type: " << type << endl;
            cout << "Balance: " << bal << endl;
            cout << "Date of Creation: " << date << endl;
            accountExist++;
        }
    }
    file.close();

    if (accountExist == 0) cout << "\nNo Account is Found From Account Number: " << this->accountType << endl;
}

// Function to find all accounts belonging to a user
vector<Account*> Account::findAccountsByUsername(const string& username)
{
    ifstream file("Account.txt");
    vector<Account*> accounts;

    if (!file)
    {
        cout << "Error opening Account.txt!\n";
        return accounts;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        string user, accNum, accType, bal, date;
        getline(ss, user, ',');
        getline(ss, accNum, ',');
        getline(ss, accType, ',');
        getline(ss, bal, ',');
        getline(ss, date, ',');

        if (Utilities::toLowerCase(user) == Utilities::toLowerCase(username))
        {
            if (Utilities::toLowerCase(accType) == Utilities::toLowerCase("Saving"))
            {
                accounts.push_back(new SavingInterestDecorator(new Saving(user, accNum, stoi(bal), date)));
            }
            else if (Utilities::toLowerCase(accType) == Utilities::toLowerCase("Chequing"))
            {
                accounts.push_back(new Chequing(user, accNum, stoi(bal), date));
            }
            else if (Utilities::toLowerCase(accType) == Utilities::toLowerCase("FixedDeposit"))
            {
                accounts.push_back(new GIC100DayDecorator(new FixedDeposit(user, accNum, stoi(bal), date)));
            }
            else if (Utilities::toLowerCase(accType) == Utilities::toLowerCase("TFSA"))
            {
                accounts.push_back(new GIC12MonthDecorator(new TFSA(user, accNum, stoi(bal), date)));
            }
            else if (Utilities::toLowerCase(accType) == Utilities::toLowerCase("RRSP"))
            {
                accounts.push_back(new RRSP(user, accNum, stoi(bal), date));
            }
        }
    }

    file.close();
    return accounts;
}

void Account::updateAccountBalance(double newBalance) const
{
    ifstream inFile("Account.txt");
    if (!inFile)
    {
        cerr << "Error: Could not open Account.txt" << endl;
        return;
    }

    ofstream tempFile("temp.txt", ios::out | ios::trunc);
    if (!tempFile)
    {
        cerr << "Error: Could not create temp file" << endl;
        return;
    }

    string line;
    bool updated = false;

    while (getline(inFile, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        string user, accNum, type, bal, date;
        getline(ss, user, ',');
        getline(ss, accNum, ',');
        getline(ss, type, ',');
        getline(ss, bal, ',');
        getline(ss, date, ',');

        if (Utilities::toLowerCase(accNum) == Utilities::toLowerCase(getAccountNumber()))
        {
            // Rewrite this line with the new balance
            tempFile << user << "," << accNum << "," << type << "," << newBalance << "," << date << '\n';
            updated = true;
        }
        else {
            // Keep the original line
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (updated) 
    {
        // Replace the original file with the updated file
        remove("Account.txt");
        rename("temp.txt", "Account.txt");
        cout << "Account updated successfully!" << endl;
    }
    else {
        cout << "Account not found!" << endl;
        remove("temp.txt"); // No need for the temp file if nothing was updated
    }
}