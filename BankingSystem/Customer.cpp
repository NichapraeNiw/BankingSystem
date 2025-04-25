#include "Customer.h"
#include "Utilities.h"
#include "History.h"
#include "Account.h";
#include "AccountFactory.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <regex>

Customer::Customer(string username, string password, string name, string email, string phone, bool inSystem)
{
    if (inSystem)
    {
        this->username = username;
        this->password = password;
        this->name = name;
        this->email = email;
        this->phone = phone;
    }
    else
    {
        bool isValid;
        // check username is not dupicated
        if (hasCustomer(username))
        {
            cout << "Error: Customer is already in a system.\n";
            isValid = false;
        }
        else
        {
            this->username = username;
            isValid = true;
        }

        // setters for validating Password, Email, and Phone
        if (!isValidPassword(password) && !isValidEmail(email) && !isValidPhone(phone))
        {
            isValid = false;
        }
        else
        {
            setPassword(password);
            setEmail(email);
            setPhone(phone);
            isValid = true;
        }

        // add new customer to file
        if (isValid)
        {
            ofstream file("Customer.txt", ios::app);
            file << username << "," << password << "," << name << "," << email << "," << phone << "\n";
            file.close();
        }
    }
}

void Customer::setPassword(string& newPassword)
{
    this->password = newPassword;
}

void Customer::setEmail(string& newEmail)
{
    if (isValidEmail(newEmail)) this->email = newEmail;
}

void Customer::setPhone(string& newPhone)
{
    if (isValidPhone(newPhone)) this->phone = newPhone;
}

// Validate Password (Min 8 chars, 1 letter, 1 number)
bool Customer::isValidPassword(const string& password)
{
    if (password.length() < 8)
    {
        cout << "Error: Password must be at least 8 characters long.\n";
        return false;
    }

    bool hasLetter = false, hasDigit = false;
    for (char ch : password)
    {
        if (isalpha(ch)) hasLetter = true;
        if (isdigit(ch)) hasDigit = true;
    }

    if (!hasLetter || !hasDigit)
    {
        cout << "Error: Password must contain both letters and numbers.\n";
        return false;
    }

    return true;
}

// Validate Email (Basic Regex Check)
bool Customer::isValidEmail(const string& email)
{
    regex pattern(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
    if (!regex_match(email, pattern))
    {
        cout << "Error: Invalid email format.\n";
        return false;
    }
    return true;
}

// Validate Phone (Only Digits, 10-15 Characters)
bool Customer::isValidPhone(const string& phone)
{
    regex pattern(R"(^\d{9,10}$)");  // 9 to 10 digit phone numbers
    if (!regex_match(phone, pattern))
    {
        cout << "Error: Phone number must contain only digits (9-10 characters).\n";
        return false;
    }
    return true;
}

void Customer::displayCustomerFromUsername(string username)
{
    ifstream file("Customer.txt");
    string line;
    bool customertExist = false;

    while (getline(file, line) && !customertExist)
    {
        if (line.empty()) continue;

        stringstream ss(line);
        string user, password, name, email, phone;
        getline(ss, user, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');

        if (Utilities::toLowerCase(user) == Utilities::toLowerCase(username))
        {
            cout << "====== Display Customer ======" << endl;
            cout << "Username: " << user << endl;
            cout << "Password: " << password << endl;
            cout << "Name: " << name << endl;
            cout << "Email: " << email << endl;
            cout << "Phone: " << phone << endl;
            customertExist = true;
        }
    }
    file.close();

    if (!customertExist) cout << "Error: Customer is NOT found from username: " << username << endl;
}

void Customer::createAccount(AccountFactory* factory, string accType, string username, double initialBalance)
{
    // check if the account type is not duplicated
    if (hasAccountType(username, accType))
    {
        cout << "Error: Customer already has a " << accType << " account.\n";
        return;
    }

    Account* newAccount = factory->createAccount(username, initialBalance);
}

void Customer::deleteAccount(string accType, string username)
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
    bool hasBalance = false;

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

        if (Utilities::toLowerCase(type) == Utilities::toLowerCase(accType) &&
            Utilities::toLowerCase(user) == Utilities::toLowerCase(username))
        {
            // cannot delete the account if balance is there
            if (stoi(bal) > 0)
            {
                cout << "Your " << accType << " account cannot be deleted, please transfer or withdraw your balance.\n";
                hasBalance = true;
            }
            else
            {
                // update log in History.txt
                History::logEvent(accNum, stoi(bal), "AccountDeleted", Utilities::getTodayString());

                // delete this line by not storing it
                updated = true;
            }
        }
        else
        {
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
    else if (!hasBalance && !updated)
    {
        cout << "Error: Account not found!" << endl;
        remove("temp.txt"); // No need for the temp file if nothing was updated
    }
}

bool Customer::hasAccountType(const string& username, const string& accountType)
{
    ifstream file("Account.txt");
    if (!file.is_open())
    {
        cout << "Error: Could not open Account.txt.\n";
        return false;
    }

    string line, user, accNum, accType, bal, date;

    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, user, ',');
        getline(ss, accNum, ',');
        getline(ss, accType, ',');
        getline(ss, bal, ',');
        getline(ss, date, ',');

        if (Utilities::toLowerCase(user) == Utilities::toLowerCase(username) && 
            Utilities::toLowerCase(accType) == Utilities::toLowerCase(accountType))
        {
            file.close();
            return true; // Found an existing account of this type
        }
    }

    file.close();
    return false; // No matching account type found
}

bool Customer::hasCustomer(string username)
{
    ifstream file("Customer.txt");
    if (!file.is_open())
    {
        cout << "Error: Could not open Customer.txt.\n";
        return false;
    }

    string line, user, pass, name, email, phone;

    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, user, ',');
        getline(ss, pass, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');

        if (Utilities::toLowerCase(user) == Utilities::toLowerCase(username))
        {
            file.close();
            return true; // Found an existing account of this type
        }
    }

    file.close();
    return false; // No matching account type found
}

void Customer::updateCustomerAccountsInterest() const
{
    vector<Account*> accounts = Account::findAccountsByUsername(getUsername());

    for (auto acc : accounts)
    {
        acc->applyInterest();
        delete acc;
    }
}

bool Customer::correctPassword(string username, string password)
{
    ifstream file("Customer.txt");
    if (!file.is_open())
    {
        cout << "Error: Could not open Customer.txt.\n";
        return false;
    }

    string line, user, pass, name, email, phone;

    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, user, ',');
        getline(ss, pass, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');

        if (Utilities::toLowerCase(user) == Utilities::toLowerCase(username) &&
            pass == password)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false; // Password Not Match
}