#include "header.h"
#include <time.h>

const char *RECORDS = "./data/records.txt";
// helper functions for getting and saving data
int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
		          &r->userId,
		         name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
            u.id,
            u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}
// functions to stay or return when a user has completed a succsful input
void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖\n");
    invalid:
        printf("\n✖ Invalid operation!\n");
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}
// function to print a success message
void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}
/**
 * @brief Validates a date
 * 
 * This function checks if a given date is valid, considering
 * month ranges, day ranges, and leap years.
 * 
 * @param date Date structure to validate
 * @return 1 if the date is valid, 0 otherwise
 */
int isValidDate(struct Date date) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (date.month < 1 || date.month > 12) return 0;
    if (date.year < 1900 || date.year > 9999) return 0;

    // Check for leap year
    if (date.month == 2 && ((date.year % 4 == 0 && date.year % 100 != 0) || date.year % 400 == 0)) {
        if (date.day < 1 || date.day > 29) return 0;
    } else {
        if (date.day < 1 || date.day > daysInMonth[date.month - 1]) return 0;
    }

    return 1;
}
/**
 * @brief Creates a new bank account for the user
 * 
 * This function guides the user through the process of creating a new bank account.
 * It collects information such as deposit date, account number, country, phone number,
 * initial deposit amount, and account type. It validates the input data and ensures
 * the account number is unique for the user before saving the new account.
 * 
 * @param u User structure of the account owner
 */
void createNewAcc(struct User u) {
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

dateInput:
    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);

    if (!isValidDate(r.deposit)) {
        printf("\n✖ Invalid date! Please enter a valid date.\n");
        goto dateInput;
    }

    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr)) {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr) {
            printf("✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
    }

    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}
// helper function of updateAccountInfo
int updateRecordFile(struct Record updatedRecord) {
    FILE *fp = fopen(RECORDS, "r");
    FILE *tempFp = fopen("temp.txt", "w");
    struct Record r;
    char userName[50];
    int found = 0;

    if (fp == NULL || tempFp == NULL) {
        printf("\nError opening file!");
        return 0;
    }

    // Copy all records to temp file, replacing the one to update
    while (getAccountFromFile(fp, userName, &r)) {
        if (r.accountNbr == updatedRecord.accountNbr) {
            // Write updated record
            // Preserve original ID and userId when writing
            fprintf(tempFp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                    r.id,  // Keep original ID
                    r.userId,  // Keep original userId
                    userName,  // Keep original username
                    updatedRecord.accountNbr,
                    updatedRecord.deposit.month,
                    updatedRecord.deposit.day,
                    updatedRecord.deposit.year,
                    updatedRecord.country,
                    updatedRecord.phone,
                    updatedRecord.amount,
                    updatedRecord.accountType);
            found = 1;
        } else {
            // Write existing record as is
            fprintf(tempFp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                    r.id,
                    r.userId,
                    userName,
                    r.accountNbr,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.amount,
                    r.accountType);
        }
    }

    fclose(fp);
    fclose(tempFp);

    // Replace original file with updated file
    remove(RECORDS);
    rename("temp.txt", RECORDS);

    return found;
}
int findAccount(struct User u, int accountNum, struct Record *record) {
    FILE *fp = fopen(RECORDS, "r");
    struct Record r;
    char userName[50];

    if (fp == NULL) {
        printf("\nError opening file!");
        return 0;
    }

    while (getAccountFromFile(fp, userName, &r)) {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNum) {
            *record = r;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
/**
 * @brief Updates information for an existing account
 * 
 * This function allows the user to update specific information for an
 * existing account, such as country and phone number.
 * 
 * @param u User structure of the account owner
 */
void updateAccountInfo(struct User u) {
    int accountNum, choice;
    struct Record record;

    system("clear");
    printf("\n\t\t====== Update Account Information ======\n");

    printf("\nEnter account number you want to update: ");
    scanf("%d", &accountNum);

    if (!findAccount(u, accountNum, &record)) {
        printf("\n\t\t✖ Account not found!");
        stayOrReturn(0, updateAccountInfo, u);
        return;
    }

    printf("\n\tCurrent Information:");
    printf("\n\tCountry: %s", record.country);
    printf("\n\tPhone: %d", record.phone);

    printf("\n\n\tWhat would you like to update?");
    printf("\n\t1. Country");
    printf("\n\t2. Phone Number");
    printf("\n\tEnter choice (1-2): ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("\nEnter new country: ");
            scanf("%s", record.country);
            break;

        case 2:
            printf("\nEnter new phone number: ");
            scanf("%d", &record.phone);
            break;

        default:
            printf("\n\t\t✖ Invalid choice!");
            stayOrReturn(0, updateAccountInfo, u);
            return;
    }

    if (updateRecordFile(record)) {
        printf("\n\t\t✔ Account information updated successfully!");
        success(u);
    } else {
        printf("\n\t\t✖ Error updating account information!");
        stayOrReturn(0, updateAccountInfo, u);
    }
}
// helper function of updateAccountInfo

// function to check all accounts
void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}
float calculateInterest(struct Record r) {
    float interestRate;
    float yearlyInterest;

    if (strcmp(r.accountType, "saving") == 0) {
        interestRate = 0.07;  // 7% annually
        return (r.amount * interestRate) / 12.0;
    }
    else if (strcmp(r.accountType, "fixed01") == 0) {
        interestRate = 0.04;  // 4% for 1-year fixed deposit
        yearlyInterest = r.amount * interestRate;
        return yearlyInterest;
    }
    else if (strcmp(r.accountType, "fixed02") == 0) {
        interestRate = 0.05;  // 5% for 2-year fixed deposit
        yearlyInterest = r.amount * interestRate * 2;  // Multiply by years
        return yearlyInterest;
    }
    else if (strcmp(r.accountType, "fixed03") == 0) {
        interestRate = 0.08;  // 8% for 3-year fixed deposit
        yearlyInterest = r.amount * interestRate * 3;  // Multiply by years
        return yearlyInterest;
    }
    else {
        return 0;  // No interest for current account
    }
}

void displayAccountDetails(struct Record r, float interest) {
    printf("\n\t≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n");
    printf("\n\t                      Account Details\n");
    printf("\n\t≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n");

    printf("\n\tAccount Number: %d", r.accountNbr);
    printf("\n\tAccount Type: %s", r.accountType);
    printf("\n\tCreation Date: %02d/%02d/%d", r.deposit.month, r.deposit.day, r.deposit.year);
    printf("\n\tCountry: %s", r.country);
    printf("\n\tPhone Number: %d", r.phone);
    printf("\n\tCurrent Balance: $%.2f", r.amount);

    if (strcmp(r.accountType, "current") == 0) {
        printf("\n\n\tNote: This is a current account. No interest will be earned.");
    } 
    else if (strstr(r.accountType, "saving") != NULL) {
        printf("\n\n\tMonthly Interest: $%.3f", interest);
        printf("\n\tYou will get $%.3f as interest on day %d of every month", 
               interest, r.deposit.day);
    } 
    else if (strstr(r.accountType, "fixed") != NULL) {
        int years = atoi(r.accountType + 5);  // Extract years from fixed01, fixed02, etc.
        printf("\n\n\tFixed Deposit Interest for %d year(s): $%.2f", 
               years, interest);
        printf("\n\tInterest will be calculated at maturity on %02d/%02d/%d", 
               r.deposit.month, r.deposit.day, r.deposit.year + years);
    }

    printf("\n\n\t≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n");
}
/**
 * @brief Displays details of a specific account
 * 
 * This function allows the user to view detailed information about
 * a specific account, including its balance and calculated interest.
 * 
 * @param u User structure of the account owner
 */
void checkAccountDetails(struct User u) {
    int accountNum;
    struct Record r;
    char userName[50];
    float interest;
    int found = 0;
    FILE *fp = fopen(RECORDS, "r");

    if (fp == NULL) {
        printf("\n\t\t✖ Error! Cannot open file.\n");
        return;
    }

    system("clear");
    printf("\n\t\t====== Account Details ======\n");
    printf("\n\tEnter account number to check: ");
    scanf("%d", &accountNum);

    while (getAccountFromFile(fp, userName, &r)) {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNum) {
            found = 1;
            interest = calculateInterest(r);
            displayAccountDetails(r, interest);
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\n\t\t✖ Account not found or unauthorized access!\n");
        stayOrReturn(0, checkAccountDetails, u);
    } else {
        stayOrReturn(1, checkAccountDetails, u);
    }
}
void makeTransaction(struct User u)
{
    struct Record r;
    char userName[50];
    int accountNum, transactionType;
    double amount;
    int found = 0;

    system("clear");
    printf("\n\t\t====== Make Transaction ======\n");

    printf("\nEnter account number: ");
    scanf("%d", &accountNum);

    // Open file for reading
    FILE *fp = fopen(RECORDS, "r");
    if (fp == NULL) {
        printf("\n\t\t✖ Error opening file!");
        return;
    }

    // Find the account
    while (getAccountFromFile(fp, userName, &r)) {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNum) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("\n\t\t✖ Account not found or unauthorized access!");
        stayOrReturn(0, makeTransaction, u);
        return;
    }

    // Check if account type allows transactions
    if (strstr(r.accountType, "fixed") != NULL) {
        printf("\n\t\t✖ Transactions are not allowed for fixed deposit accounts!");
        stayOrReturn(0, makeTransaction, u);
        return;
    }

    // Get transaction type
    printf("\nSelect transaction type:");
    printf("\n1. Deposit");
    printf("\n2. Withdraw");
    printf("\nEnter choice (1-2): ");
    scanf("%d", &transactionType);

    if (transactionType != 1 && transactionType != 2) {
        printf("\n\t\t✖ Invalid transaction type!");
        stayOrReturn(0, makeTransaction, u);
        return;
    }

    // Get amount
    printf("\nEnter amount: $");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("\n\t\t✖ Invalid amount! Amount must be positive.");
        stayOrReturn(0, makeTransaction, u);
        return;
    }

    // Handle withdraw specific validation
    if (transactionType == 2) {
        if (amount > r.amount) {
            printf("\n\t\t✖ Insufficient funds! Current balance: $%.2f", r.amount);
            stayOrReturn(0, makeTransaction, u);
            return;
        }
        r.amount -= amount;
        printf("\n\t\t✔ Withdrawn: $%.2f", amount);
    } else {
        r.amount += amount;
        printf("\n\t\t✔ Deposited: $%.2f", amount);
    }

    // Update the record
    if (updateRecordFile(r)) {
        printf("\n\t\t✔ Transaction successful!");
        printf("\n\t\tNew balance: $%.2f", r.amount);
        success(u);
    } else {
        printf("\n\t\t✖ Error updating account!");
        stayOrReturn(0, makeTransaction, u);
    }
}
void removeExistingAccount(struct User u)
{
    struct Record r;
    char userName[50];
    int accountNum;
    int found = 0;
    char confirm;
    int forceDelete = 0;

    system("clear");
    printf("\n\t\t====== Remove Existing Account ======\n");

    printf("\nEnter the account number to remove: ");
    scanf("%d", &accountNum);

    // Open file for reading
    FILE *fp = fopen(RECORDS, "r");
    if (fp == NULL) {
        printf("\n\t\t✖ Error opening file!");
        return;
    }

    // First check if account exists and belongs to user
    while (getAccountFromFile(fp, userName, &r)) {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNum) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("\n\t\t✖ Account not found or unauthorized access!");
        stayOrReturn(0, removeExistingAccount, u);
        return;
    }

    // Show account details before deletion
    printf("\n\t=== Account Details ===");
    printf("\n\tAccount Number: %d", r.accountNbr);
    printf("\n\tAccount Type: %s", r.accountType);
    printf("\n\tBalance: $%.2f", r.amount);
    printf("\n\tCountry: %s", r.country);

    // Confirm deletion
    printf("\n\nWARNING: This action cannot be undone!");
    
    // If balance is not zero, ask about force deletion
    if (r.amount > 0) {
        printf("\n\t⚠ WARNING: This account has a balance of $%.2f", r.amount);
        printf("\n\tDo you want to (a) Cancel, (b) Withdraw funds first, or (c) Force Delete? (a/b/c): ");
        scanf(" %c", &confirm);

        if (confirm == 'a' || confirm == 'A') {
            printf("\n\t✔ Account removal cancelled.");
            stayOrReturn(1, removeExistingAccount, u);
            return;
        }
        else if (confirm == 'b' || confirm == 'B') {
            printf("\n\t⚠ Please withdraw funds before closing the account.");
            stayOrReturn(0, removeExistingAccount, u);
            return;
        }
        else if (confirm == 'c' || confirm == 'C') {
            forceDelete = 1;
        }
        else {
            printf("\n\t✖ Invalid option. Cancelling account removal.");
            stayOrReturn(1, removeExistingAccount, u);
            return;
        }
    }
    else {
        printf("\nDo you really want to remove this account? (y/n): ");
        scanf(" %c", &confirm);

        if (confirm != 'y' && confirm != 'Y') {
            printf("\n\t✔ Account removal cancelled.");
            stayOrReturn(1, removeExistingAccount, u);
            return;
        }
    }

    // Proceed with removal
    FILE *tempFp = fopen("temp.txt", "w");
    if (tempFp == NULL) {
        printf("\n\t\t✖ Error creating temporary file!");
        return;
    }

    // Reopen original file
    fp = fopen(RECORDS, "r");
    found = 0;

    // Copy all records except the one to be deleted
    while (getAccountFromFile(fp, userName, &r)) {
        if (r.accountNbr != accountNum || strcmp(userName, u.name) != 0) {
            fprintf(tempFp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                    r.id,
                    r.userId,
                    userName,
                    r.accountNbr,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.amount,
                    r.accountType);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(tempFp);

    // Replace original file with updated file
    if (found) {
        remove(RECORDS);
        rename("temp.txt", RECORDS);
        printf("\n\t\t✔ Account successfully removed!");
        success(u);
    } else {
        remove("temp.txt");
        printf("\n\t\t✖ Error removing account!");
        stayOrReturn(0, removeExistingAccount, u);
    }
}
/**
 * @brief Transfers account ownership to another user
 * 
 * This function allows a user to transfer ownership of an account
 * to another registered user. It includes validation of the target
 * user and confirmation prompts.
 * 
 * @param u User structure of the current account owner
 */
void transferOwnership(struct User u) {
    struct Record r;
    char userName[50];
    char targetUser[50];
    int accountNum;
    int found = 0;
    char confirm;

    system("clear");
    printf("\n\t\t====== Transfer Account Ownership ======\n");

    // Get account number to transfer
    printf("\nEnter the account number to transfer: ");
    scanf("%d", &accountNum);

    // Find the account and verify ownership
    FILE *fp = fopen(RECORDS, "r");
    if (fp == NULL) {
        printf("\n\t\t✖ Error opening file!");
        return;
    }

    while (getAccountFromFile(fp, userName, &r)) {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNum) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("\n\t\t✖ Account not found or unauthorized access!");
        stayOrReturn(0, transferOwnership, u);
        return;
    }

    // Show account details before transfer
    printf("\n\t=== Account Details ===");
    printf("\n\tAccount Number: %d", r.accountNbr);
    printf("\n\tAccount Type: %s", r.accountType);
    printf("\n\tBalance: $%.2f", r.amount);
    printf("\n\tCountry: %s", r.country);

    // Get target user
    printf("\n\nEnter username to transfer this account to: ");
    scanf("%s", targetUser);

    // Verify target user exists
    if (!checkUserExists(targetUser)) {
        printf("\n\t\t✖ Target user does not exist!");
        stayOrReturn(0, transferOwnership, u);
        return;
    }

    // Prevent transfer to self
    if (strcmp(u.name, targetUser) == 0) {
        printf("\n\t\t✖ Cannot transfer account to yourself!");
        stayOrReturn(0, transferOwnership, u);
        return;
    }

    // Confirm transfer
    printf("\n\nWARNING: This action cannot be undone!");
    printf("\nDo you want to transfer this account to %s? (y/n): ", targetUser);
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y') {
        printf("\n\t✔ Account transfer cancelled.");
        stayOrReturn(1, transferOwnership, u);
        return;
    }

    // Proceed with transfer
    FILE *tempFp = fopen("temp.txt", "w");
    if (tempFp == NULL) {
        printf("\n\t\t✖ Error creating temporary file!");
        return;
    }

    // Reopen original file
    fp = fopen(RECORDS, "r");
    found = 0;
    struct Record tempR;
    char tempUserName[50];

    // Copy all records, updating the transferred account
    while (getAccountFromFile(fp, tempUserName, &tempR)) {
        if (tempR.accountNbr == accountNum && strcmp(tempUserName, u.name) == 0) {
            // Write the record with new owner
            fprintf(tempFp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                    tempR.id,
                    tempR.userId,
                    targetUser,  // New owner
                    tempR.accountNbr,
                    tempR.deposit.month,
                    tempR.deposit.day,
                    tempR.deposit.year,
                    tempR.country,
                    tempR.phone,
                    tempR.amount,
                    tempR.accountType);
            found = 1;
        } else {
            // Write other records as is
            fprintf(tempFp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                    tempR.id,
                    tempR.userId,
                    tempUserName,
                    tempR.accountNbr,
                    tempR.deposit.month,
                    tempR.deposit.day,
                    tempR.deposit.year,
                    tempR.country,
                    tempR.phone,
                    tempR.amount,
                    tempR.accountType);
        }
    }

    fclose(fp);
    fclose(tempFp);

    // Replace original file with updated file
    if (found) {
        remove(RECORDS);
        rename("temp.txt", RECORDS);
        printf("\n\t\t✔ Account successfully transferred to %s!", targetUser);
        success(u);
    } else {
        remove("temp.txt");
        printf("\n\t\t✖ Error transferring account!");
        stayOrReturn(0, transferOwnership, u);
    }
}