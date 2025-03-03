/**
 * @file main.c
 * @brief Main entry point for the ATM Management System
 * 
 * This file contains the main program entry point and the menu handling
 * functions for the ATM Management System. It manages the initial login/register
 * menu and the main operation menu after successful authentication.
 */

#include "header.h"

/**
 * @brief Displays the main menu and handles user selections
 * 
 * This function displays the main menu of the ATM system after successful
 * login, presenting options for account management and transactions.
 * It processes the user's selection and calls the appropriate function.
 * 
 * @param u User structure of the logged-in user
 */
void mainMenu(struct User u)
{
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        updateAccountInfo(u);
        break;
    case 3:
        checkAccountDetails(u);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        makeTransaction(u);
        break;
    case 6:
        removeExistingAccount(u);
        break;
    case 7:
        transferOwnership(u);
        break;
    case 8:
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
    }
};

/**
 * @brief Displays the initial menu for login or registration
 * 
 * This function presents the initial menu where users can choose to
 * login with existing credentials or register a new account.
 * It handles the authentication process before proceeding to the main menu.
 * 
 * @param u Pointer to User structure to store the authenticated user's information
 */
void initMenu(struct User *u)
{
    int r = 0;
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                printf("\n\nLogin Succesful!");
            }
            else
            {
                printf("\nWrong password!! or User Name\n");
                exit(1);
            }
            r = 1;
            break;
        case 2:
            registerMenu(u);    
            r = 1;
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n");
        }
    }
};

/**
 * @brief Main entry point of the ATM Management System
 * 
 * Initializes the program, displays the initial menu for authentication,
 * and proceeds to the main menu after successful login or registration.
 * 
 * @return 0 on successful program execution
 */
int main()
{
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}