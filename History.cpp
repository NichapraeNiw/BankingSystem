#include "History.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
#include <algorithm>

History::History(string accNum, double amt, string t)
	: accountNumber(accNum), amount(amt), type(t)
{
	this->date = Utilities::getTodayString();
}

void History::logEvent(string accNum, double amt, string type, string date)
{
	ofstream file("History.txt", ios::app);
	file << accNum << "," << amt << "," << type << "," << date << "\n";
	file.close();
}

void History::displayHistoryLogFromAccountNumber(string accountNumber)
{
    ifstream file("History.txt");
    string line;
    int accountExist = 0;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        string accNum, amt, type, date;
        getline(ss, accNum, ',');
        getline(ss, amt, ',');
        getline(ss, type, ',');
        getline(ss, date, ',');

        if (accNum == accountNumber)
        {
            cout << accNum << "," << amt << "," << type << "," << date << "\n";
            accountExist++;
        }
    }
    file.close();

    if (accountExist == 0) cout << "No History Log From this Account: " << accountNumber << endl;
}

string History::getLastInterestDate(string accountNumber)
{
    ifstream file("History.txt");
    if (!file.is_open())
    {
        cerr << "Error: Unable to open History.txt" << endl;
        return "";
    }

    string line, lastInterestDate = "";

    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        string accNum, amt, type, date;
        getline(ss, accNum, ',');
        getline(ss, amt, ',');
        getline(ss, type, ',');
        getline(ss, date, ',');

        if (Utilities::toLowerCase(accNum) == Utilities::toLowerCase(accountNumber) && 
            Utilities::toLowerCase(type) == "interest")
        {
            lastInterestDate = date;
            continue;
        }
        if (Utilities::toLowerCase(accNum) == Utilities::toLowerCase(accountNumber)
            && Utilities::toLowerCase(type) == "accountcreated")
        {
            lastInterestDate = date;
            continue;
        }
    }

    file.close();
    return lastInterestDate;
}