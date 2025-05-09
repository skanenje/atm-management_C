#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    printf("\n\n\t\t\t\tUsername: ");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};
/**
 * @brief Retrieves the password for a given user
 * 
 * This function searches the users file for a user with the specified
 * name and returns their password if found.
 * 
 * @param u User structure containing the username to look up
 * @return The user's password if found, or "no user found" if not found
 */
const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            // Use strdup to create a dynamically allocated copy of the password
            return strdup(userChecker.password);
        }
    }

    fclose(fp);
    return "no user found";
}

int getLastUserId() {
    FILE *fp;
    struct User userChecker;
    int lastId = -1;
    
    fp = fopen(USERS, "r");
    if (fp == NULL) {
        return 0;  // If file doesn't exist, start with ID 0
    }
    
    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF) {
        if (userChecker.id > lastId) {
            lastId = userChecker.id;
        }
    }
    
    fclose(fp);
    return lastId + 1;
}

/**
 * @brief Checks if a username already exists
 * 
 * This function searches the users file to determine if a
 * given username is already registered in the system.
 * 
 * @param username Username to check
 * @return 1 if the user exists, 0 otherwise
 */
int checkUserExists(char username[50]) {
    FILE *fp;
    struct User userChecker;
    
    fp = fopen(USERS, "r");
    if (fp == NULL) {
        return 0;  // File doesn't exist, so user doesn't exist
    }
    
    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF) {
        if (strcmp(userChecker.name, username) == 0) {
            fclose(fp);
            return 1;  // User exists
        }
    }
    
    fclose(fp);
    return 0;  // User doesn't exist
}

/**
 * @brief Saves a user to the users file
 * 
 * This function appends a new user record to the users file.
 * 
 * @param u User structure containing the information to save
 */
void saveUserToFile(struct User u) {
    FILE *fp;
    fp = fopen(USERS, "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(fp, "%d %s %s\n", u.id, u.name, u.password);
    fclose(fp);
}
/**
 * @brief Displays the registration menu and registers a new user
 * 
 * This function handles the user registration process, including
 * username validation, secure password input, and saving the new
 * user to the users file.
 * 
 * @param u Pointer to User structure to store the new user's information
 */
void registerMenu(struct User *u) {
    struct termios oflags, nflags;
    char password[50];
    
    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Registration\n");
    
    // Flag to control registration loop
    int registrationFailed = 0;
    
    do {
        // Get username
        printf("\n\n\t\t\t\tEnter username: ");
        scanf("%s", u->name);
        
        // Check if user already exists
        if (checkUserExists(u->name)) {
            printf("\n\t\t\tUser already exists! Please choose a different username.\n");
            registrationFailed = 1;
            continue;  // Restart the loop
        } else {
            registrationFailed = 0;
        }
        
        // Get password (with hidden input)
        printf("\n\n\t\t\t\tEnter password: ");
        
        // Disable echo
        tcgetattr(fileno(stdin), &oflags);
        nflags = oflags;
        nflags.c_lflag &= ~ECHO;
        nflags.c_lflag |= ECHONL;
        
        if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
            perror("tcsetattr");
            return;
        }
        
        scanf("%s", password);
        strcpy(u->password, password);
        
        // Restore terminal settings
        if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
            perror("tcsetattr");
            return;
        }
        
    } while (registrationFailed);
    
    // Generate new user ID
    u->id = getLastUserId();
    
    // Save user to file
    saveUserToFile(*u);
    
    printf("\n\t\t\t\tRegistration successful!\n");
    printf("\n\t\t\tPress any key to continue...");
    getchar();
    getchar();
}