# ATM Management System Documentation

## Overview

The ATM Management System is a C-based application that simulates the functionality of an Automated Teller Machine (ATM) system. It provides a command-line interface for users to perform various banking operations such as creating accounts, making transactions, and managing account information.

## System Architecture

The system is organized into several components:

### Data Structures

1. **User Structure** (`struct User`):
   - Stores user authentication information
   - Contains user ID, username, and password

2. **Record Structure** (`struct Record`):
   - Stores account information
   - Contains account details such as account number, balance, type, and owner information

3. **Date Structure** (`struct Date`):
   - Stores date information for deposits and withdrawals
   - Contains day, month, and year fields

### Core Components

1. **Authentication System** (`auth.c`):
   - Handles user registration and login
   - Manages user credentials and validation
   - Provides secure password input

2. **Account Management** (`system.c`):
   - Handles account creation and deletion
   - Manages account information updates
   - Processes financial transactions
   - Calculates interest based on account type

3. **Main Program** (`main.c`):
   - Provides the entry point and menu system
   - Coordinates between authentication and account management

### Data Storage

The system uses text files to store data:

1. **Users File** (`data/users.txt`):
   - Stores user information in the format: `id username password`
   - Each line represents one user

2. **Records File** (`data/records.txt`):
   - Stores account records in the format: `id userId username accountNumber date country phone amount accountType`
   - Each record contains all account information

## Functionality

### User Authentication

1. **Registration**:
   - New users can register with a unique username and password
   - System validates username uniqueness
   - Passwords are entered securely (hidden input)

2. **Login**:
   - Users can log in with their credentials
   - System validates the username and password

### Account Management

1. **Account Creation**:
   - Users can create new bank accounts
   - System collects account details (date, country, phone, initial deposit)
   - Users can select account type (saving, current, fixed deposit)

2. **Account Information**:
   - Users can view all their accounts
   - Users can check specific account details
   - System displays account information and calculated interest

3. **Account Updates**:
   - Users can update account information (country, phone number)
   - System validates and saves the updated information

### Financial Operations

1. **Transactions**:
   - Users can deposit money into their accounts
   - Users can withdraw money from their accounts
   - System validates transaction amounts and account balances

2. **Interest Calculation**:
   - System calculates interest based on account type:
     - Savings: 7% annually, calculated monthly
     - Current: No interest
     - Fixed Deposit (1 year): 4% annually
     - Fixed Deposit (2 years): 5% annually
     - Fixed Deposit (3 years): 8% annually

3. **Account Removal**:
   - Users can remove their accounts
   - System provides safety checks for accounts with balances

4. **Ownership Transfer**:
   - Users can transfer account ownership to another user
   - System validates the target user and confirms the transfer

## Function Reference

### Authentication Functions

- `loginMenu(char a[50], char pass[50])`: Displays login menu and captures credentials
- `getPassword(struct User u)`: Retrieves password for a user
- `registerMenu(struct User *u)`: Handles user registration
- `checkUserExists(char username[50])`: Checks if a username exists

### System Functions

- `createNewAcc(struct User u)`: Creates a new account
- `mainMenu(struct User u)`: Displays main menu
- `checkAllAccounts(struct User u)`: Shows all user accounts
- `checkAccountDetails(struct User u)`: Shows specific account details
- `calculateInterest(struct Record r)`: Calculates account interest
- `displayAccountDetails(struct Record r, float interest)`: Displays account details
- `updateAccountInfo(struct User u)`: Updates account information
- `makeTransaction(struct User u)`: Processes financial transactions
- `removeExistingAccount(struct User u)`: Removes an account
- `transferOwnership(struct User u)`: Transfers account ownership

### Helper Functions

- `getAccountFromFile(FILE *ptr, char name[50], struct Record *r)`: Reads account from file
- `saveAccountToFile(FILE *ptr, struct User u, struct Record r)`: Saves account to file
- `stayOrReturn(int notGood, void f(struct User u), struct User u)`: Handles navigation
- `success(struct User u)`: Displays success message
- `isValidDate(struct Date date)`: Validates date input
- `updateRecordFile(struct Record updatedRecord)`: Updates record in file
- `findAccount(struct User u, int accountNum, struct Record *record)`: Finds account by number

## Usage Examples

### Creating a New Account

1. Log in to the system
2. Select option 1 from the main menu
3. Enter the date, account number, country, phone, deposit amount
4. Select account type
5. The system will create the account and display a success message

### Making a Transaction

1. Log in to the system
2. Select option 5 from the main menu
3. Enter the account number
4. Select transaction type (deposit or withdraw)
5. Enter the amount
6. The system will process the transaction and update the balance

### Checking Account Details

1. Log in to the system
2. Select option 3 from the main menu
3. Enter the account number
4. The system will display account details and calculated interest

## Error Handling

The system includes various error checks:

- Validation of date inputs
- Checking for duplicate account numbers
- Verification of sufficient funds for withdrawals
- Confirmation prompts for critical operations
- Input validation for menu selections

## Building and Running

To build the system:

```bash
make
```

To run the system:

```bash
./atm
```

To clean object files:

```bash
make clean
```