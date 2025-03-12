#pragma once
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
    Customer(string user, string pass, string n, string e, string p);

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }

    static Customer loadCustomers(string targetUsername);
    void saveCustomer() const;
    void displayCustomer() const;
};
