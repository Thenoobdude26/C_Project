#include <stdio.h>
#include <string.h>
#include "common.h"

struct User users[MAX_USERS];
int user_count = 0;
char current_user[50];

void saveUsersToFile() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%s %s %s %s %d %d\n", users[i].username, users[i].password,
                users[i].email, users[i].phone, users[i].frequentRouteCount, users[i].paymentMethodCount);
        for (int j = 0; j < users[i].frequentRouteCount; j++) {
            fprintf(file, "%s\n", users[i].frequentRoutes[j]);
        }
        for (int j = 0; j < users[i].paymentMethodCount; j++) {
            fprintf(file, "%s\n", users[i].paymentMethods[j]);
        }
    }
    fclose(file);
}

void loadUsersFromFile() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) return;
    while (fscanf(file, "%s %s %s %s %d %d", users[user_count].username, users[user_count].password,
                  users[user_count].email, users[user_count].phone, &users[user_count].frequentRouteCount,
                  &users[user_count].paymentMethodCount) != EOF) {
        for (int j = 0; j < users[user_count].frequentRouteCount; j++) {
            fscanf(file, "%s", users[user_count].frequentRoutes[j]);
        }
        for (int j = 0; j < users[user_count].paymentMethodCount; j++) {
            fscanf(file, "%s", users[user_count].paymentMethods[j]);
        }
        user_count++;
    }
    fclose(file);
}

void registerUser() {
    if (user_count >= MAX_USERS) {
        printf("User limit reached! Cannot register more users.\n");
        return;
    }
    printf("Enter username: ");
    scanf("%s", users[user_count].username);
    printf("Enter password: ");
    scanf("%s", users[user_count].password);
    printf("Enter email: ");
    scanf("%s", users[user_count].email);
    printf("Enter phone number: ");
    scanf("%s", users[user_count].phone);
    users[user_count].frequentRouteCount = 0;
    users[user_count].paymentMethodCount = 0;
    user_count++;
    saveUsersToFile();
    printf("Registration successful!\n");
}

int loginUser() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful!\n");
            strcpy(current_user, username);
            return 1;
        }
    }
    printf("Invalid username or password!\n");
    return 0;
}

void viewProfile() {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, current_user) == 0) {
            printf("\nUser Profile:\n");
            printf("Username: %s\n", current_user);
            printf("Email: %s\n", users[i].email);
            printf("Phone: %s\n", users[i].phone);
            break;
        }
    }
    displayTickets();
}

void updateProfile() {
    char newPassword[50], newEmail[50], newPhone[15];
    printf("Enter new password (or press Enter to skip): ");
    scanf("%s", newPassword);
    printf("Enter new email (or press Enter to skip): ");
    scanf("%s", newEmail);
    printf("Enter new phone number (or press Enter to skip): ");
    scanf("%s", newPhone);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, current_user) == 0) {
            if (strlen(newPassword) > 0) strcpy(users[i].password, newPassword);
            if (strlen(newEmail) > 0) strcpy(users[i].email, newEmail);
            if (strlen(newPhone) > 0) strcpy(users[i].phone, newPhone);
            saveUsersToFile();
            printf("Profile updated successfully!\n");
            return;
        }
    }
    printf("User not found!\n");
}

int main() {
    int choice;
    loadUsersFromFile();

    while (1) {
        printf("\nMain Menu\n");
        printf("1. Register User\n");
        printf("2. Login\n");
        printf("3. View Profile\n");
        printf("4. Update Password\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: registerUser(); break;
            case 2:
                if (loginUser()) {
                    printf("Welcome, %s!\n", current_user);
                    mainMenu(); // Enter ticket system
                }
                break;
            case 3: viewProfile(); break;
            case 4: updatePassword(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}