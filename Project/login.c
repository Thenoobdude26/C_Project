#include <stdio.h>
#include <string.h>
#include <time.h>
#include "common.h"

struct User users[MAX_USERS];
int user_count = 0;
char current_user[50];
int current_user_is_admin = 0;
static Notification notifications[MAX_NOTIFICATIONS];
static int notificationCount = 0;

// Save user data to file
void saveUsersToFile() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%s %s %s %s %d %d\n", users[i].username, users[i].password,
                users[i].email, users[i].phone, users[i].frequentRouteCount, users[i].isAdmin);
        for (int j = 0; j < users[i].frequentRouteCount; j++) {
            fprintf(file, "%s\n", users[i].frequentRoutes[j]);
        }
    }
    fclose(file);
}

// Load user data from file
void loadUsersFromFile() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) return;
    while (fscanf(file, "%s %s %s %s %d %d", users[user_count].username, users[user_count].password,
                  users[user_count].email, users[user_count].phone, &users[user_count].frequentRouteCount,
                  &users[user_count].isAdmin) != EOF) {
        for (int j = 0; j < users[user_count].frequentRouteCount; j++) {
            fscanf(file, "%s", users[user_count].frequentRoutes[j]);
        }
        user_count++;
    }
    fclose(file);
}

// Save notifications to file
void saveNotificationsToFile() {
    FILE *file = fopen("notifications.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing notifications!\n");
        return;
    }
    for (int i = 0; i < notificationCount; i++) {
        fprintf(file, "%s %s %ld\n", notifications[i].username, notifications[i].message, notifications[i].timestamp);
    }
    fclose(file);
}

// Load notifications from file
void loadNotificationsFromFile() {
    FILE *file = fopen("notifications.txt", "r");
    if (file == NULL) return;
    while (fscanf(file, "%s %[^\n] %ld", notifications[notificationCount].username,
                  notifications[notificationCount].message, &notifications[notificationCount].timestamp) != EOF) {
        notifications[notificationCount].isRead = 0;  // Simplified: no read status
        notificationCount++;
    }
    fclose(file);
}

// Add a new notification for a user
void addNotification(const char* username, const char* message) {
    if (notificationCount >= MAX_NOTIFICATIONS) {
        for (int i = 0; i < MAX_NOTIFICATIONS - 1; i++) {
            notifications[i] = notifications[i + 1];
        }
        notificationCount--;
    }

    strcpy(notifications[notificationCount].username, username);
    strcpy(notifications[notificationCount].message, message);
    notifications[notificationCount].timestamp = time(NULL);
    notifications[notificationCount].isRead = 0;
    notificationCount++;
    saveNotificationsToFile();
}

// Display notifications for the current user
void showUserNotifications(const char* username) {
    printf("\n=== Your Notifications ===\n");
    int count = 0;
    
    for (int i = 0; i < notificationCount; i++) {
        if (strcmp(notifications[i].username, username) == 0) {
            count++;
            char timeStr[20];
            strftime(timeStr, 20, "%Y-%m-%d %H:%M:%S", localtime(&notifications[i].timestamp));
            
            printf("%d. %s - %s\n", count, notifications[i].message, timeStr);
        }
    }
    
    if (count == 0) {
        printf("No notifications found.\n");
    }
}

// Delete a notification
void deleteNotification(const char* username, int index) {
    int userNotifCount = 0;
    int toDelete = -1;
    
    for (int i = 0; i < notificationCount; i++) {
        if (strcmp(notifications[i].username, username) == 0) {
            userNotifCount++;
            if (userNotifCount == index) {
                toDelete = i;
                break;
            }
        }
    }
    
    if (toDelete == -1) {
        printf("Invalid notification index.\n");
        return;
    }
    
    for (int i = toDelete; i < notificationCount - 1; i++) {
        notifications[i] = notifications[i + 1];
    }
    
    notificationCount--;
    saveNotificationsToFile();
    printf("Notification deleted.\n");
}

// Simplified payment simulation
int processPayment(const char* username, float amount) {
    printf("\n=== Payment Processing (Simulation) ===\n");
    printf("Amount to pay: RM%.2f\n", amount);
    printf("Proceed with payment? (1 for Yes, 0 for No): ");
    int choice;
    scanf("%d", &choice);
    
    if (choice != 1) {
        printf("Payment cancelled.\n");
        return 0;
    }
    
    printf("Payment of RM%.2f successful (simulated)!\n", amount);
    
    char notifMsg[NOTIF_MSG_LEN];
    snprintf(notifMsg, NOTIF_MSG_LEN, "Payment of RM%.2f for ticket booking completed", amount);
    addNotification(username, notifMsg);
    
    return 1;
}

// Notification menu for the user
void notificationMenu() {
    int choice;
    do {
        showUserNotifications(current_user);
        
        printf("\n1. Delete notification\n");
        printf("2. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            printf("Enter notification number: ");
            int notifNum;
            scanf("%d", &notifNum);
            deleteNotification(current_user, notifNum);
        }
    } while (choice != 2);
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
    printf("Is this user an admin? (1 for Yes, 0 for No): ");
    scanf("%d", &users[user_count].isAdmin);
    users[user_count].frequentRouteCount = 0;
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
            current_user_is_admin = users[i].isAdmin;
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
            printf("Frequent Routes:\n");
            if (users[i].frequentRouteCount == 0) {
                printf("- None\n");
            } else {
                for (int j = 0; j < users[i].frequentRouteCount; j++) {
                    printf("- %s\n", users[i].frequentRoutes[j]);
                }
            }
            break;
        }
    }
    displayTickets();
}

void updateProfile() {
    char newPassword[50], newEmail[50], newPhone[15];
    printf("Enter new password (or press Enter to skip): ");
    scanf(" %[^\n]", newPassword);
    getchar();
    printf("Enter new email (or press Enter to skip): ");
    scanf(" %[^\n]", newEmail);
    getchar();
    printf("Enter new phone number (or press Enter to skip): ");
    scanf(" %[^\n]", newPhone);
    getchar();

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

void addFrequentRoute() {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, current_user) == 0) {
            if (users[i].frequentRouteCount >= MAX_FREQUENT_ROUTES) {
                printf("Cannot add more frequent routes! Limit is %d.\n", MAX_FREQUENT_ROUTES);
                return;
            }
            printf("Enter route to save (e.g., 'KL to Penang'): ");
            char route[50];
            scanf(" %[^\n]", route);
            strcpy(users[i].frequentRoutes[users[i].frequentRouteCount++], route);
            saveUsersToFile();
            printf("Route saved successfully!\n");
            return;
        }
    }
}

void userMenu() {
    int choice;
    do {
        printf("\n===== User Menu =====\n");
        printf("1. Manage Tickets\n");
        printf("2. View Profile\n");
        printf("3. Update Profile\n");
        printf("4. Add Frequent Route\n");
        printf("5. View Notifications\n");
        printf("6. Logout\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: mainMenu(); break;
            case 2: viewProfile(); break;
            case 3: updateProfile(); break;
            case 4: addFrequentRoute(); break;
            case 5: notificationMenu(); break;
            case 6: printf("Logging out...\n"); return;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (1);
}

int main() {
    int choice;
    loadUsersFromFile();
    loadNotificationsFromFile();
    // Load routes (moved to ticket.c)
    FILE *file = fopen("tickets.txt", "r");
    if (file) {
        while (fscanf(file, "%s %[^\n] %[^\n] %d", tickets[ticketCount].name, tickets[ticketCount].route,
                      tickets[ticketCount].time, &tickets[ticketCount].seatNumber) != EOF) {
            ticketCount++;
        }
        fclose(file);
    }

    while (1) {
        printf("\nMain Menu\n");
        printf("1. Register User\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: registerUser(); break;
            case 2:
                if (loginUser()) {
                    printf("Welcome, %s!\n", current_user);
                    if (current_user_is_admin) {
                        printf("You are logged in as an admin.\n");
                        adminMainMenu();
                    } else {
                        userMenu();
                    }
                }
                break;
            case 3: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}