#include "InterestDecorator.h"
#include "Utilities.h"
#include <sstream>
#include <fstream>

InterestDecorator::InterestDecorator(Account* account)
    : Account(*account)
{
    decoratedAccount = account;
}

void InterestDecorator::displayAccountDetail() const
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