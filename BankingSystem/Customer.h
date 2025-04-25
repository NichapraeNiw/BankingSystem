#pragma once
#include "AccountFactory.h"
#include <iostream>

using namespace std;

class Customer
{
private:
    string username;
    string password;
    string name;
    string email;
    string phone;

public:
    Customer(string username, string password, string name, string email, string phone, bool inSystem);

    // Getters
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }

    // Setters
    void setPassword(string& newPassword);
    void setEmail(string& newEmail);
    void setPhone(string& newPhone);

    static bool isValidPassword(const string& password);
    static bool isValidEmail(const string& email);
    static bool isValidPhone(const string& phone);

    // Functions
    static void displayCustomerFromUsername(string username);
    void createAccount(AccountFactory* factory, string accType, string username, double initialBalance);
    void deleteAccount(string accType, string username);
    void updateCustomerAccountsInterest() const;
    static bool hasAccountType(const string& username, const string& accountType); // check if the account is duplicated or not in the text file
    static bool hasCustomer(string username);
    static bool correctPassword(string username, string password);
};