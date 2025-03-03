/**
 * @file header.h
 * @brief Header file for the ATM Management System
 * 
 * This file contains all the necessary structure definitions and function
 * declarations used throughout the ATM Management System. It defines the
 * data structures for users, accounts, and transactions, as well as the
 * function prototypes for authentication and system operations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct Date
 * @brief Structure to store date information
 * 
 * Used for tracking deposit and withdrawal dates for accounts
 */
struct Date
{
    int month, day, year;
};

/**
 * @struct Record
 * @brief Structure to store account record information
 * 
 * Contains all fields for each record of an account including personal
 * information, account details, and transaction dates
 */
struct Record
{
    int id;                 /**< Unique record identifier */
    int userId;             /**< User ID of the account owner */
    char name[100];         /**< Account holder's name */
    char country[100];      /**< Account holder's country */
    int phone;              /**< Account holder's phone number */
    char accountType[10];   /**< Type of account (saving, current, fixed01, fixed02, fixed03) */
    int accountNbr;         /**< Unique account number */
    double amount;          /**< Current balance in the account */
    struct Date deposit;    /**< Date of deposit/account creation */
    struct Date withdraw;   /**< Date of last withdrawal */
};

/**
 * @struct User
 * @brief Structure to store user information
 * 
 * Contains user authentication and identification details
 */
struct User
{
    int id;                 /**< Unique user identifier */
    char name[50];          /**< Username for login */
    char password[50];      /**< User's password */
};

/* Authentication Functions */

/**
 * @brief Displays the login menu and captures user credentials
 * 
 * @param a Array to store the entered username
 * @param pass Array to store the entered password
 */
void loginMenu(char a[50], char pass[50]);

/**
 * @brief Retrieves the password for a given user
 * 
 * @param u User structure containing the username to look up
 * @return The password as a string if found, "no user found" otherwise
 */
const char *getPassword(struct User u);

/**
 * @brief Displays the registration menu and registers a new user
 * 
 * @param u Pointer to User structure to store the new user's information
 */
void registerMenu(struct User *u);

/**
 * @brief Checks if a username already exists in the system
 * 
 * @param username Username to check
 * @return 1 if the user exists, 0 otherwise
 */
int checkUserExists(char username[50]);

/* System Functions */

/**
 * @brief Creates a new bank account for the user
 * 
 * @param u User structure of the account owner
 */
void createNewAcc(struct User u);

/**
 * @brief Displays the main menu of the ATM system
 * 
 * @param u User structure of the logged-in user
 */
void mainMenu(struct User u);

/**
 * @brief Displays all accounts owned by the user
 * 
 * @param u User structure of the account owner
 */
void checkAllAccounts(struct User u);

/**
 * @brief Displays details of a specific account
 * 
 * @param u User structure of the account owner
 */
void checkAccountDetails(struct User u);

/**
 * @brief Calculates interest for an account based on its type
 * 
 * @param r Record structure of the account
 * @return The calculated interest amount
 */
float calculateInterest(struct Record r);

/**
 * @brief Displays detailed account information including interest
 * 
 * @param r Record structure of the account
 * @param interest Calculated interest for the account
 */
void displayAccountDetails(struct Record r, float interest);

/**
 * @brief Updates information for an existing account
 * 
 * @param u User structure of the account owner
 */
void updateAccountInfo(struct User u);

/**
 * @brief Updates a record in the records file
 * 
 * @param updatedRecord The record with updated information
 * @return 1 if successful, 0 otherwise
 */
int updateRecordFile(struct Record updatedRecord);

/**
 * @brief Processes deposit or withdrawal transactions
 * 
 * @param u User structure of the account owner
 */
void makeTransaction(struct User u);

/**
 * @brief Removes an existing account
 * 
 * @param u User structure of the account owner
 */
void removeExistingAccount(struct User u);

/**
 * @brief Transfers account ownership to another user
 * 
 * @param u User structure of the current account owner
 */
void transferOwnership(struct User u);