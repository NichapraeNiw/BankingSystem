#include <iostream>
#include <sstream>
#include <fstream>
#include "Bank.h"
#include "Customer.h"
#include "SavingFactory.h"
#include "ChequingFactory.h"
#include "FixedDepositFactory.h"
#include "TFSAFactory.h"
#include "RRSPFactory.h"
#include "Utilities.h"

using namespace std;

// Initialize static member
Bank* Bank::instance = nullptr;

// Static method to get the singleton instance
Bank* Bank::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Bank();
	}
	return instance;
}

// Static method if dynamically create the Bank class
void Bank::destroyInstance()
{
	delete instance;
	instance = nullptr;
}

Customer* Bank::login()
{
	string username, password, name, email, phone;
	bool isSuccess = false;

	while (!isSuccess)
	{
		cout << "=== LOGIN ===" << endl;
		cout << "USERNAME: ";
		cin >> username;

		if (!Customer::hasCustomer(username)) // Check if user exists
		{
			cout << "Error: Username not found.\n" << endl;
			continue;
		}

		cout << "PASSWORD: ";
		cin >> password;

		if (!Customer::correctPassword(username, password)) // Check password
		{
			cout << "Error: Incorrect password.\n" << endl;
			continue;
		}

		isSuccess = true; // all parameters are valid
	}

	cout << "\n************CUSTOMER FOUND************\n";
	return new Customer(username, password, name, email, phone, true);
}

Customer* Bank::signUp()
{
	string username, password, name, email, phone;
	bool isSuccess = false;

	while (!isSuccess)
	{
		cout << "=== SIGN IN ===" << endl;
		cout << "USERNAME: ";
		cin >> username;
		if (Customer::hasCustomer(username))
		{
			cout << "Error: Customer is already in a system.\n" << endl;
			continue;
		}

		cout << "PASSWORD: ";
		cin >> password;
		if (!Customer::isValidPassword(password))
		{
			cout << endl;
			continue;
		}

		cout << "FULL NAME: ";
		cin.ignore();
		getline(cin, name);

		cout << "EMAIL: ";
		cin >> email;
		if (!Customer::isValidEmail(email))
		{
			cout << endl;
			continue;
		}

		cout << "PHONE: ";
		cin >> phone;
		if (!Customer::isValidPhone(phone))
		{
			cout << endl;
			continue;
		}

		isSuccess = true; // all parameters are valid
	}

	cout << "\n************CUSTOMER CREATED************\n";
	return new Customer(username, password, name, email, phone, false);
}

void Bank::BankingConsole()
{
	Customer* cus = nullptr; // Store customer

	while (true)
	{
		int option;

		cout << "===== Banking Console =====\n";
		cout << "1. Login\n";
		cout << "2. Sign Up\n";
		cout << "0. EXIT()\n";
		cout << "You pick option: ";
		cin >> option;

		switch (option)
		{
		case 1:
			cus = login();
			if (!cus) cout << "\nblank\n";
			BankingOption(cus);
			continue;

		case 2:
			cus = signUp();
			BankingOption(cus);
			continue;

		case 0:
			cout << "\nExiting...\n\n";
			break;

		default:
			cout << "\nINVALID OPTION!\n";
			continue;
		}
		break;
	}

	delete cus;
}

void Bank::BankingOption(Customer* cus)
{
	{
		// ====== for Bank UI console when creating customer -> account ======
		cus->displayCustomerFromUsername(cus->getUsername());
		cout << "\nCustomer Accounts Loading...\n";
		cus->updateCustomerAccountsInterest();
		cout << "\nLoading Completed!\n";

		while (true)
		{
			int option;

			cout << "\n ===== SELECT OPTION ===== \n";
			cout << "1. Create Account \n";
			cout << "2. Delete Account \n";
			cout << "3. Deposit \n";
			cout << "4. Withdraw \n";
			cout << "5. Transfer \n";
			cout << "6. Display Account Detail \n";
			cout << "0. EXIT()\n";
			cout << "You pick option: ";
			cin >> option;

			switch (option)
			{
			case 1:
				createAccount(cus);
				continue;

			case 2:
				deleteAccount(cus);
				continue;

			case 3:
				deposit(cus);
				continue;

			case 4:
				withdraw(cus);
				continue;

			case 5:
				transfer(cus);
				continue;

			case 6:
				displayYourAccount(cus);
				continue;

			case 0:
				cout << "\nExiting...\n\n";
				break;

			default:
				cout << "\nINVALID OPTION!\n";
				continue;
			}

			break;
		}
	}
}

void Bank::createAccount(Customer* cus)
{
	AccountFactory* saving = new SavingFactory();
	AccountFactory* chequing = new ChequingFactory();
	AccountFactory* fixed = new FixedDepositFactory();
	AccountFactory* tfsa = new TFSAFactory();
	AccountFactory* rrsp = new RRSPFactory();

	while (true)
	{
		int accType;
		double amount = 0.00;

		cout << "\nChoose Account Type To Create: " << endl;
		cout << "1. Saving" << endl;
		cout << "2. Chequing" << endl;
		cout << "3. FixedDeposit" << endl;
		cout << "4. TFSA" << endl;
		cout << "5. RRSP" << endl;
		cout << "0. EXIT()\n";

		cout << "You pick option: ";
		cin >> accType;

		switch (accType)
		{
		case 1:
			if (Customer::hasAccountType(cus->getUsername(), "Saving"))
			{
				cout << "\nError: Saving account has already existed for username: " << cus->getUsername() << endl;
				continue;
			}

			cout << "Enter amount: ";
			cin >> amount;

			cus->createAccount(saving, "Saving", cus->getUsername(), amount);
			cout << endl << "Saving Account is created!" << endl;
			continue;

		case 2:
			if (Customer::hasAccountType(cus->getUsername(), "Chequing"))
			{
				cout << "\nError: Chequing account has already existed for username: " << cus->getUsername() << endl;
				continue;
			}

			cout << "Enter amount: ";
			cin >> amount;

			cus->createAccount(chequing, "Chequing", cus->getUsername(), amount);
			cout << endl << "Chequing Account is created!" << endl;
			continue;

		case 3:
			if (Customer::hasAccountType(cus->getUsername(), "FixedDeposit"))
			{
				cout << "\nError: Fixed Deposit account has already existed for username: " << cus->getUsername() << endl;
				continue;
			}

			cout << "Enter amount: ";
			cin >> amount;

			cus->createAccount(fixed, "FixedDeposit", cus->getUsername(), amount);
			cout << endl << "Fixed Deposit Account is created!" << endl;
			continue;

		case 4:
			if (Customer::hasAccountType(cus->getUsername(), "TFSA"))
			{
				cout << "\nError: TFSA account has already existed for username: " << cus->getUsername() << endl;
				continue;
			}

			cout << "Enter amount: ";
			cin >> amount;

			cus->createAccount(tfsa, "TFSA", cus->getUsername(), amount);
			cout << endl << "TFSA Account is created!" << endl;
			continue;

		case 5:
			if (Customer::hasAccountType(cus->getUsername(), "RRSP"))
			{
				cout << "\nError: RRSP account has already existed for username: " << cus->getUsername() << endl;
				continue;
			}

			cout << "Enter amount: ";
			cin >> amount;

			cus->createAccount(rrsp, "RRSP", cus->getUsername(), amount);
			cout << endl << "RRSP Account is created!" << endl;
			continue;

		case 0:
			cout << "\nExiting...\n";
			break;

		default:
			cout << "\nINVALID OPTION!\n";
			continue;
		}

		break;
	}

	delete saving;
	delete chequing;
	delete fixed;
	delete tfsa;
	delete rrsp;
}

void Bank::deleteAccount(Customer* cus)
{
	while (true)
	{
		int deleteOption;

		cout << "\n ==== What account do you want do delete? ==== \n";
		cout << "1. Saving\n";
		cout << "2. Chequing\n";
		cout << "3. Fixed Deposit\n";
		cout << "4. TFSA\n";
		cout << "5. RRSP\n";
		cout << "0. EXIT()\n";

		cout << "You pick option: ";
		cin >> deleteOption;

		switch (deleteOption)
		{
		case 1:
			cout << endl;
			cus->deleteAccount("Saving", cus->getUsername());
			continue;

		case 2:
			cout << endl;
			cus->deleteAccount("Chequing", cus->getUsername());
			continue;

		case 3:
			cout << endl;
			cus->deleteAccount("FixedDeposit", cus->getUsername());
			continue;

		case 4:
			cout << endl;
			cus->deleteAccount("TFSA", cus->getUsername());
			continue;

		case 5:
			cout << endl;
			cus->deleteAccount("RRSP", cus->getUsername());
			continue;

		case 0:
			cout << "\nExiting...\n";
			break;

		default:
			cout << "\nINVALID OPTION!\n";
			continue;
		}

		break;
	}
}

void Bank::deposit(Customer* cus)
{
	while (true)
	{
		bool found = false;
		int deposit;
		double amount = 0.00;

		cout << "\n ==== What account do you want to deposit? ==== \n";
		cout << "1. Saving\n";
		cout << "2. Chequing\n";
		cout << "3. Fixed Deposit\n";
		cout << "4. TFSA\n";
		cout << "5. RRSP\n";
		cout << "0. EXIT()\n";

		cout << "You pick option: ";
		cin >> deposit;

		vector<Account*> accounts = Account::findAccountsByUsername(cus->getUsername());
		switch (deposit)
		{
		case 1:
			for (Account* acc : accounts)
			{
				if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("Saving"))
				{
					cout << "Enter amount to deposit: ";
					cin >> amount;

					cout << endl;
					acc->deposit(amount);

					found = true;
					continue;
				}
			}

			if (!found)
				cout << endl << "Error: Saving accout has not been created." << endl;

			continue;

		case 2:
			for (Account* acc : accounts)
			{
				if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("Chequing"))
				{
					cout << "Enter amount to deposit: ";
					cin >> amount;

					cout << endl;
					acc->deposit(amount);

					found = true;
					continue;
				}
			}

			if (!found)
				cout << endl << "Error: Chequing accout has not been created." << endl;

			continue;

		case 3:
			for (Account* acc : accounts)
			{
				if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("FixedDeposit"))
				{
					cout << "Enter amount to deposit: ";
					cin >> amount;

					cout << endl;
					acc->deposit(amount);

					found = true;
					continue;
				}
			}

			if (!found)
				cout << endl << "Error: Fixed Deposit accout has not been created." << endl;

			continue;

		case 4:
			for (Account* acc : accounts)
			{
				if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("TFSA"))
				{
					cout << "Enter amount to deposit: ";
					cin >> amount;

					cout << endl;
					acc->deposit(amount);

					found = true;
					continue;
				}
			}

			if (!found)
				cout << endl << "Error: TFSA accout has not been created." << endl;

			continue;

		case 5:
			for (Account* acc : accounts)
			{
				if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("RRSP"))
				{
					cout << "Enter amount to deposit: ";
					cin >> amount;

					cout << endl;
					acc->deposit(amount);

					found = true;
					continue;
				}
			}

			if (!found)
				cout << endl << "Error: RRSP accout has not been created." << endl;

			continue;

		case 0:
			// Clean up memory
			for (Account* acc : accounts)
			{
				delete acc;
			}
			cout << "\nExiting...\n";
			break;

		default:
			cout << "\nINVALID OPTION!\n";
			continue;
		}

		break;
	}
}

void Bank::withdraw(Customer* cus)
{
	{
		while (true)
		{
			bool found = false;
			int withdraw;
			double amount = 0.00;

			cout << "\n ==== What account do you want to withdraw? ==== \n";
			cout << "1. Saving\n";
			cout << "2. Chequing\n";
			cout << "3. Fixed Deposit\n";
			cout << "4. TFSA\n";
			cout << "5. RRSP\n";
			cout << "0. EXIT()\n";

			cout << "You pick option: ";
			cin >> withdraw;

			vector<Account*> accounts = Account::findAccountsByUsername(cus->getUsername());
			switch (withdraw)
			{
			case 1:
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("Saving"))
					{
						cout << "Enter amount to withdraw: ";
						cin >> amount;

						cout << endl;
						acc->withdraw(amount);

						found = true;
						continue;
					}
				}

				if (!found)
					cout << endl << "Error: Saving accout has not been created." << endl;

				continue;

			case 2:
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("Chequing"))
					{
						cout << "Enter amount to withdraw: ";
						cin >> amount;

						cout << endl;
						acc->withdraw(amount);

						found = true;
						continue;
					}
				}

				if (!found)
					cout << endl << "Error: Chequing accout has not been created." << endl;

				continue;

			case 3:
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("FixedDeposit"))
					{
						cout << "Enter amount to withdraw: ";
						cin >> amount;

						cout << endl;
						acc->withdraw(amount);

						found = true;
						continue;
					}
				}

				if (!found)
					cout << endl << "Error: Fixed Deposit accout has not been created." << endl;

				continue;

			case 4:
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("TFSA"))
					{
						cout << "Enter amount to withdraw: ";
						cin >> amount;

						cout << endl;
						acc->withdraw(amount);

						found = true;
						continue;
					}
				}

				if (!found)
					cout << endl << "Error: TFSA accout has not been created." << endl;

				continue;

			case 5:
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("RRSP"))
					{
						cout << "Enter amount to withdraw: ";
						cin >> amount;

						cout << endl;
						acc->withdraw(amount);

						found = true;
						continue;
					}
				}

				if (!found)
					cout << endl << "Error: RRSP accout has not been created." << endl;

				continue;

			case 0:
				// Clean up memory
				for (Account* acc : accounts)
				{
					delete acc;
				}
				cout << "\nExiting...\n";
				break;

			default:
				cout << "\nINVALID OPTION!\n";
				continue;
			}

			break;
		}
	}
}

void Bank::transfer(Customer* cus)
{
	while (true)
	{
		double amount = 0.00;
		int transfer, toAccount;

		cout << "\n ==== What account do you want to transfer from? ==== \n";
		cout << "1. Saving\n";
		cout << "2. Chequing\n";
		cout << "3. Fixed Deposit\n";
		cout << "4. TFSA\n";
		cout << "5. RRSP\n";
		cout << "0. EXIT()\n";

		cout << "You pick option: ";
		cin >> transfer;

		vector<Account*> accounts = Account::findAccountsByUsername(cus->getUsername());
		Account* acc1 = nullptr;
		Account* acc2 = nullptr;

		switch (transfer)
		{
		case 1:
			// Find the Saving account
			for (Account* acc : accounts)
			{
				if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("Saving"))
				{
					acc1 = new Saving(acc->getUsername(), acc->getAccountNumber(), acc->getBalance(), acc->getCreationDate());
					break;
				}
			}

			break;

		case 2:
			// Find the Chequing account
			for (Account* acc : accounts)
			{
				if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("Chequing"))
				{
					acc1 = new Chequing(acc->getUsername(), acc->getAccountNumber(), acc->getBalance(), acc->getCreationDate());
					break;
				}
			}

			break;

		case 3:
			// Find the Fixed Deposit account
			for (Account* acc : accounts)
			{
				if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("FixedDeposit"))
				{
					acc1 = new FixedDeposit(acc->getUsername(), acc->getAccountNumber(), acc->getBalance(), acc->getCreationDate());
					break;
				}
			}

			break;

		case 4:
			// Find the TFSA account
			for (Account* acc : accounts)
			{
				if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("TFSA"))
				{
					acc1 = new TFSA(acc->getUsername(), acc->getAccountNumber(), acc->getBalance(), acc->getCreationDate());
					break;
				}
			}

			break;

		case 5:
			// Find the RRSP account
			for (Account* acc : accounts)
			{
				if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("RRSP"))
				{
					acc1 = new RRSP(acc->getUsername(), acc->getAccountNumber(), acc->getBalance(), acc->getCreationDate());
					break;
				}
			}

			break;

		case 0:
			cout << "\nExiting...\n";
			break;

		default:
			cout << "\nINVALID OPTION!\n";
			continue;
		}

		// back to menu if choose exit
		if (transfer == 0)
		{
			// Clean up memory
			for (Account* acc : accounts)
			{
				delete acc;
			}

			delete acc1;
			delete acc2;

			break;
		}
		// continue the loop if the account1 not found
		else if (acc1 == nullptr)
		{
			cout << "\nError: No matching account found for the selected type!" << endl;

			delete acc1;
			continue;
		}
		// ask for amount to transfer if account1 is found
		else if (acc1 != nullptr)
		{
			cout << "Enter the transfer amount: ";
			cin >> amount;

			// continue the loop if account1 has insuffient amount to transfer
			if (acc1->getBalance() < amount)
			{
				cout << "\nYour " << acc1->getAccountType() << " has insuffcient amount." << endl;

				delete acc1;
				continue;
			}
		}

		while (transfer != 0)
		{
			// Transfer to another account
			cout << "\n==== Transfer to which account? ====\n";
			cout << "1. Saving\n";
			cout << "2. Chequing\n";
			cout << "3. Fixed Deposit\n";
			cout << "4. TFSA\n";
			cout << "5. RRSP\n";
			cout << "0. EXIT()\n";

			cout << "You pick option: ";
			cin >> toAccount;

			switch (toAccount)
			{
			case 1:
				// continue the loop if pick the same account
				if (toAccount == transfer)
				{
					cout << "\nError: Cannot pick the same account. Please re-select an account for the transfer destination.\n";
					continue;
				}

				// Find Chequing account
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("Saving"))
					{
						acc2 = new Saving(acc->getUsername(), acc->getAccountNumber(), acc->getBalance(), acc->getCreationDate());
						break;
					}
				}
				break;

			case 2:
				// continue the loop if pick the same account
				if (toAccount == transfer)
				{
					cout << "\nError: Cannot pick the same account. Please re-select an account for the transfer destination.\n";
					continue;
				}

				// Find Chequing account
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("Chequing"))
					{
						acc2 = new Chequing(acc->getUsername(), acc->getAccountNumber(), acc->getBalance(), acc->getCreationDate());
						break;
					}
				}
				break;

			case 3:
				// continue the loop if pick the same account
				if (toAccount == transfer)
				{
					cout << "\nError: Cannot pick the same account. Please re-select an account for the transfer destination.\n";
					continue;
				}

				// Find Fixed Deposit account
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("FixedDeposit"))
					{
						acc2 = new FixedDeposit(acc->getUsername(), acc->getAccountNumber(), acc->getBalance(), acc->getCreationDate());
						break;
					}
				}
				break;

			case 4:
				// continue the loop if pick the same account
				if (toAccount == transfer)
				{
					cout << "\nError: Cannot pick the same account. Please re-select an account for the transfer destination.\n";
					continue;
				}

				// Find TFSA account
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("TFSA"))
					{
						acc2 = new TFSA(acc->getUsername(), acc->getAccountNumber(), acc->getBalance(), acc->getCreationDate());
						break;
					}
				}
				break;

			case 5:
				// continue the loop if pick the same account
				if (toAccount == transfer)
				{
					cout << "\nError: Cannot pick the same account. Please re-select an account for the transfer destination.\n";
					continue;
				}

				// Find RRSP account
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("RRSP"))
					{
						acc2 = new RRSP(acc->getUsername(), acc->getAccountNumber(), acc->getBalance(), acc->getCreationDate());
						break;
					}
				}
				break;

			case 0:
				cout << "\nExiting...\n";
				break;

			default:
				cout << "\nINVALID OPTION!\n";
				continue;
			}

			// continue the loop if the account2 not found
			if (acc2 == nullptr && toAccount != 0)
			{
				cout << "\nNo matching account found for the transfer destination! Please re-select an account for the transfer destination." << endl;

				delete acc2;
				continue;
			}
			break;
		}

		// back to transfer menu if choose exit
		if (toAccount == 0)
		{
			// Clean up memory
			for (Account* acc : accounts)
			{
				delete acc;
			}

			delete acc1;
			delete acc2;
			continue;
		}

		// Perform transfer
		cout << endl;
		acc1->transfer(amount, acc2);

		// Clean up memory
		for (Account* acc : accounts)
		{
			delete acc;
		}

		delete acc1;
		delete acc2;

		continue;
	}
}

void Bank::displayYourAccount(Customer* cus)
{
	{
		while (true)
		{
			bool found = false;
			int detail;
			double amount = 0.00;

			cout << "\n==== What account do you want to see the detail? ====\n";
			cout << "1. Saving\n";
			cout << "2. Chequing\n";
			cout << "3. Fixed Deposit\n";
			cout << "4. TFSA\n";
			cout << "5. RRSP\n";
			cout << "0. EXIT()\n";

			cout << "You pick option: ";
			cin >> detail;

			vector<Account*> accounts = Account::findAccountsByUsername(cus->getUsername());
			switch (detail)
			{
			case 1:
				for (auto acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("Saving"))
					{
						acc->displayAccountDetail();
						found = true;
						continue;
					}
				}

				if (!found)
					cout << endl << "Error: Saving accout has not been created." << endl;

				continue;

			case 2:
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("Chequing"))
					{
						acc->displayAccountDetail();
						found = true;
						continue;
					}
				}

				if (!found)
					cout << endl << "Error: Chequing accout has not been created." << endl;

				continue;

			case 3:
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("FixedDeposit"))
					{
						acc->displayAccountDetail();
						found = true;
						continue;
					}
				}

				if (!found)
					cout << endl << "Error: Fixed Deposit accout has not been created." << endl;

				continue;

			case 4:
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("TFSA"))
					{
						acc->displayAccountDetail();
						found = true;
						continue;
					}
				}

				if (!found)
					cout << endl << "Error: TFSA accout has not been created." << endl;

				continue;

			case 5:
				for (Account* acc : accounts)
				{
					if (Utilities::toLowerCase(acc->getAccountType()) == Utilities::toLowerCase("RRSP"))
					{
						acc->displayAccountDetail();
						found = true;
						continue;
					}
				}

				if (!found)
					cout << endl << "Error: RRSP accout has not been created." << endl;

				continue;

			case 0:
				// Clean up memory
				for (auto acc : accounts)
				{
					delete acc;
				}
				cout << "\nExiting...\n";
				break;

			default:
				cout << "\nINVALID OPTION!\n";
				continue;
			}

			break;
		}
	}
}