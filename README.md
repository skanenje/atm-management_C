# ATM Management System

A comprehensive C-based ATM (Automated Teller Machine) Management System that simulates banking operations with user authentication, account management, and transaction processing.

## Features

- **User Authentication**: Secure login and registration system
- **Account Management**: Create, update, and remove accounts
- **Transaction Processing**: Deposit and withdraw funds
- **Account Details**: View account information and calculate interest
- **Multiple Account Types**: Support for savings, current, and fixed deposit accounts
- **Ownership Transfer**: Transfer account ownership between users

## Project Structure

```
atm-management_C/
├── data/                  # Data storage directory
│   ├── users.txt          # User credentials storage
│   └── records.txt        # Account records storage
├── src/                   # Source code directory
│   ├── header.h           # Header file with declarations
│   ├── main.c             # Main program entry point
│   ├── auth.c             # Authentication functions
│   └── system.c           # Core ATM functionality
└── Makefile               # Build configuration
```

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/atm-management_C.git
   cd atm-management_C
   ```

2. Compile the program:
   ```
   make
   ```

3. Run the ATM system:
   ```
   ./atm
   ```

## Usage

### First-time Use

1. Register a new user account
2. Login with your credentials
3. Create a new bank account

### Regular Operations

- **Create Account**: Set up a new bank account with initial deposit
- **Update Information**: Modify account details like country and phone number
- **Check Accounts**: View all your accounts or specific account details
- **Make Transactions**: Deposit or withdraw funds
- **Remove Account**: Close an existing account
- **Transfer Ownership**: Transfer an account to another user

## Account Types

- **Savings Account**: Earns 7% interest annually, calculated monthly
- **Current Account**: No interest
- **Fixed Deposit**:
  - 1 Year (fixed01): 4% interest
  - 2 Years (fixed02): 5% interest
  - 3 Years (fixed03): 8% interest

## Data Storage

- User data is stored in `data/users.txt`
- Account records are stored in `data/records.txt`

## License

[Add your license information here]