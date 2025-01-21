#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
// void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);
void registerMenu(struct User *u);
int checkUserExists(char username[50]);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void checkAccountDetails(struct User u);
float calculateInterest(struct Record r);
void displayAccountDetails(struct Record r, float interest);
void updateAccountInfo(struct User u);
int updateRecordFile(struct Record updatedRecord);
