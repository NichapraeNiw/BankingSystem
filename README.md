# Group 6: Console-based Bank System

### Student Name:
1.	Nattanicha Nilsriphaiwan
2.	Ying Su

### Course:
COMP 4603 – Advanced C++

### Instructor:
Frederic Guo

### Introduction:
A simple command-line application is designed to simulate a basic banking system. It allows users to manage accounts, perform transactions, and track account history. This project aims to provide a foundational understanding of banking systems while implementing object-oriented programming principles.

### Objectives:
- Account Management: Create, delete, and manage multiple account types (e.g., Savings, Chequing, Fixed Deposit, TFSA, RRSP).
- Transactions: Perform deposit, withdrawal, and transfer operations between accounts.
- Transaction History: Track and store transaction history for each account.
- Balance Inquiry: Allow users to check account balances.
- Interest Calculation: Apply interest on relevant account types.
- Security: Basic password protection for accounts.

### Scope:
This project focuses on implementing core banking features like account management, transactions, balance inquiries, and transaction history. It supports multiple account types and basic security features. The system is command-line based and designed for learning and simulation purposes.
 
### UML Diagram:
![image](https://github.com/user-attachments/assets/edb922ba-2e74-47d8-879d-422d6771c722)
https://lucid.app/lucidchart/947c72c2-5939-4e61-be81-3bb8e94eb0c8/edit?viewport_loc=-5249%2C-636%2C6026%2C2847%2C0_0&invitationId=inv_7db3b363-fb8a-4eb9-93ba-1a63c268eb7d
 
### Design Patterns:
**Singleton Design Pattern**
- Singleton is applied in Bank class.
- This ensures that only one instance of the Bank class exists.
- It provides a global access point to manage customers and accounts.
- It is implemented by making the constructor private and using a static method to get the instance.
![image](https://github.com/user-attachments/assets/48d4ed13-712e-4034-8f66-5f6d9a832dc4)

**Factory Method Pattern**
- AccountFactory class is an interface that defines a method to create accounts.
- Each account type implements the factory to create specific accounts. (SavingFactory, ChequingFactory, FixedDopositFactory, TFSAFactory, and RRSPFactory) 
- This pattern allows flexibility when adding new account types without modifying existing code.
![Banking System](https://github.com/user-attachments/assets/39b22c07-5656-4dad-a3eb-ed809cab93eb)

 
**Decorator Pattern**
- InterestDecorator allows adding dynamic interest calculation to accounts without modifying the base Account class.
- InterestDecorator is an abstract class that wraps around a concrete Account object.
- Concrete decorators override InterestDecorator methods, and each cconcrete decorator class has a different way of interest calculation.
(SavingInterestDecorator, 100DayGICDecorator, and 12MonthGICDecorator)
![Banking System](https://github.com/user-attachments/assets/fd5f7d27-0bf7-4008-9274-b55d26db091e)


### Command Line User Interface:
The interface uses a do-while loop to continuously display the menu options until the user chooses to exit. The process works as follows:
- Show menu options (e.g., Login, Sign Up, etc.).
- Get user input and execute the corresponding function using a switch statement.
- Repeat the process until the user selects the exit option, which terminates the loop.
- A user can create accounts by providing their name, a username, a valid password, email, and phone number. User accounts are protected by passwords.
- A user must login to the system with verified username and password first before performing various transactions, like deposit, withdrawal, and transferring money.
- Method to apply interest to eligible accounts is called when the user login to their account, whether the interest is applied will go through the validation process in the method.

**Login or Sign-up UI**

![image](https://github.com/user-attachments/assets/68da5a6c-c6e1-4575-820b-48e437b74fa0)
 
**Banking option UI (once an account is created or login):**

![image](https://github.com/user-attachments/assets/9c4e67d4-f7fd-43a2-aaca-9988b76834b4)

**Interest UI**

![image](https://github.com/user-attachments/assets/74a64d34-0ff4-49a2-9471-4f6ea4b8a74f)

### Data Persistence:
- There are 3 text files used to record program data and history, which mimics 3 tables in a database:
  - Customer.txt for customer records
  - Account.txt for account records
  - History.txt for transaction history
- The Bank class is responsible for reading, writing, and updating these text files.
- Whenever a new object such as a Customer, Account, or transaction History is created, the data will be added to or updated in the respective text files.
- Since all data is stored in these text files, we can always look up and retrieve information directly from the files whenever needed.
- This ensures data persistence and consistency even if the program is closed and restarted in future.

**Customer.txt**

![image](https://github.com/user-attachments/assets/719fbb19-2726-4c7d-aa83-4b89db71c4e1)

**Account.txt**

![image](https://github.com/user-attachments/assets/ff04f1e4-bc36-47f1-b4bc-b9a2bc092290)
 
**History.txt**

![image](https://github.com/user-attachments/assets/38d2dcf4-1146-4312-b20d-d9b15af43a85)
 
### Future Improvements or Extensions
- Hashing the passwords before storing them for data persistence.
- Storing data in a database instead of in text files.
- Different levels of users and privilege.
- More convenient methods in different classes for better user experience.
