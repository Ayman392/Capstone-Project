#include <stdio.h>
#include <string.h>

// Define a structure for user accounts
struct User {
    char username[50];
    char password[50];
};

// Function to sign up a new user
void signUp(struct User users[], int *userCount) {
    struct User newUser;
    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);

    // Add the new user to the users array
    users[*userCount] = newUser;
    (*userCount)++;

    printf("User signed up successfully!\n");
}

int main() {
    struct User users[100]; // Array to store user accounts
    int userCount = 0; // Number of users

    int choice;
    while (1) {
        printf("1. Sign Up\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signUp(users, &userCount);
                break;
            case 2:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

/*
### Explanation:

1. **Structure Definition**: The `User` structure stores the username and password.
2. **Sign-Up Function**:
   - Prompts the user to enter a username and password.
   - Stores the new user's data in the `users` array.
   - Increments the `userCount` to keep track of the number of registered users.
3. **Main Function**:
   - Displays a menu with options to sign up or exit.
   - Executes the selected option by calling the `signUp` function or exiting the program.

This simple program allows users to sign up by creating an account with a username and password. Feel free to expand upon it to include other functionalities such as login, product management, and more!
*/