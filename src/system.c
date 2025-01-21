#include "header.h"
#include <time.h>

const char *RECORDS = "./data/records.txt";

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
            r.id,         // Remove & and use . instead of ->
            u.id,         // Remove & and use . instead of ->
            u.name,       // Remove & and use . instead of ->
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
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

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
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
float calculateInterest(struct Record r) {
    float interestRate;
    float monthlyInterest;
    
    // Set interest rate based on account type
    if (strcmp(r.accountType, "saving") == 0) {
        interestRate = 0.07;  // 7%
    }
    else if (strcmp(r.accountType, "fixed01") == 0) {
        interestRate = 0.04;  // 4%
    }
    else if (strcmp(r.accountType, "fixed02") == 0) {
        interestRate = 0.05;  // 5%
    }
    else if (strcmp(r.accountType, "fixed03") == 0) {
        interestRate = 0.08;  // 8%
    }
    else {
        return 0;  // No interest for current account
    }
    
    // Calculate monthly interest
    monthlyInterest = (r.amount * interestRate) / 12.0;
    return monthlyInterest;
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
    } else {
        printf("\n\n\tMonthly Interest: $%.3f", interest);
        printf("\n\tYou will get $%.3f as interest on day %d of every month",
               interest, r.deposit.day);
    }
    
    printf("\n\n\t≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n");
}

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