#include "Utilities.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

string Utilities::getTodayString()
{
    time_t now = time(nullptr);

    tm localTime;
    if (localtime_s(&localTime, &now) != 0)
    {
        throw runtime_error("Failed to get local time.");
    }

    ostringstream oss;
    oss << put_time(&localTime, "%Y-%m-%d"); // YYYY-MM-DD
    return oss.str();
}

int Utilities::getDaysBetween(string date1, string date2)
{
    {
        tm t1 = {};
        tm t2 = {};

        char dash; // To consume the '-' character while parsing
        istringstream ss1(date1), ss2(date2);

        ss1 >> t1.tm_year >> dash >> t1.tm_mon >> dash >> t1.tm_mday;
        ss2 >> t2.tm_year >> dash >> t2.tm_mon >> dash >> t2.tm_mday;

        t1.tm_year -= 1900;
        t1.tm_mon -= 1;
        t2.tm_year -= 1900;
        t2.tm_mon -= 1;

        time_t time1 = mktime(&t1);
        time_t time2 = mktime(&t2);

        return difftime(time2, time1) / (60 * 60 * 24);
    }
}

string Utilities::toLowerCase(const string& str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), tolower);
    return result;
}

string Utilities::generateUniqueAccountNumber()
{
    set<string> existingAccounts;
    ifstream file("account.txt");

    // Read existing account numbers from file
    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        string username, accNum, accountType, balance;

        getline(ss, username, ',');
        getline(ss, accNum, ','); // Read account number
        getline(ss, accountType, ',');
        getline(ss, balance, ',');

        existingAccounts.insert(accNum);
    }
    file.close();

    // Seed random generator
    srand(time(0));

    string newAccountNumber;
    do {
        int randomNum = rand() % 100000; // Generates a number between 0 - 99999
        stringstream ss;
        ss << setw(5) << setfill('0') << randomNum; // Formats number as 5-digit string
        newAccountNumber = ss.str();
    } while (existingAccounts.find(newAccountNumber) != existingAccounts.end());

    return newAccountNumber;
}

tm Utilities::stringToDate(const string& date)
{
    tm t = {};
    sscanf_s(date.c_str(), "%d-%d-%d", &t.tm_year, &t.tm_mon, &t.tm_mday);
    t.tm_year -= 1900; // Adjust for struct tm format
    t.tm_mon -= 1;
    return t;
}