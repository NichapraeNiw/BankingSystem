#pragma once
#include <iostream>
using namespace std;

class Utilities
{
public:
    static string getTodayString();

    // Function to calculate days between two dates
    // This is accurate if leap year happens
    static int getDaysBetween(string date1, string date2);

    static string toLowerCase(const string& str);

    static string generateUniqueAccountNumber();

    static tm stringToDate(const string& date);
};