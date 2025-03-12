#include <fstream>
#include <vector>
#include <sstream>
#include "Customer.h"

Customer::Customer(string user, string pass, string n, string e, string p)
    : username(user), password(pass), name(n), email(e), phone(p) 
{}

Customer Customer::loadCustomers(string targetUsername)
{
    ifstream file("bank_data.txt");
    string line;

    while (getline(file, line))
    {
        if (line == "[CUSTOMERS]") continue;
        stringstream ss(line);
        string username, password, name, email, phone;

        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');

        if (username == targetUsername)
        {
            file.close();
            return Customer(username, password, name, email, phone);
        }
    }

    file.close();
    throw runtime_error("Customer not found");
}

void Customer::saveCustomer() const
{
    ofstream file("bank_data.txt", ios::app);
    if (file.is_open())
    {
        file << username << "," << password << "," << name << "," << email << "," << phone << "\n";
        file.close();
    }
}

void Customer::displayCustomer() const
{
    cout << username << "," << password << "," << name << "," << email << "," << phone << "\n";
}