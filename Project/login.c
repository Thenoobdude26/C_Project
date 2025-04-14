#include <stdio.h>
#include <string.h>
#include <time.h>
#include "common.h"

struct User users[MAX_USERS];
int user_count = 0;
char current_user[50];
int current_user_is_admin = 0;
Notification notifications[MAX_NOTIFICATIONS];  // Moved here from global scope
int notificationCount = 0;  // Moved here from global scope

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

void saveNotificationsToFile() {
    FILE *file = fopen("notifications.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing notifications!\n");
        return;
    }
    for (int i = 0; i < notificationCount; i++) {
        fprintf(file, "%s %s %ld %d\n", notifications[i].username, notifications[i].message,
                notifications[i].timestamp, notifications[i].isRead);
    }
    fclose(file);
}

void loadNotificationsFromFile() {
    FILE *file = fopen("notifications.txt", "r");
    if (file == NULL) return;
    while (fscanf(file, "%s %s %ld %d", notifications[notificationCount].username,
                  notifications[notificationCount].message, &notifications[notificationCount].timestamp,
                  &notifications[notificationCount].isRead) != EOF) {
        notificationCount++;
    }
    fclose(file);
}

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

void showUserNotifications(const char* username) {
    printf("\n=== Your Notifications ===\n");
    int count = 0;
    
    for (int i = 0; i < notificationCount; i++) {
        if (strcmp(notifications[i].username, username) == 0) {
            count++;
            char timeStr[20];
            strftime(timeStr, 20, "%Y-%m-%d %H:%M:%S", localtime(&notifications[i].timestamp));
            
            printf("%d. [%s] %s - %s\n", 
                   count,
                   notifications[i].isRead ? "Read" : "Unread",
                   notifications[i].message,
                   timeStr);
        }
    }
    
    if (count == 0) {
        printf("No notifications found.\n");
    }
}

void markNotificationAsRead(const char* username, int index) {
    int userNotifCount = 0;
    
    for (int i = 0; i < notificationCount; i++) {
        if (strcmp(notifications[i].username, username) == 0) {
            userNotifCount++;
            if (userNotifCount == index) {
                notifications[i].isRead = 1;
                saveNotificationsToFile();
                printf("Notification marked as read.\n");
                return;
            }
        }
    }
    
    printf("Invalid notification index.\n");
}

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

int processPayment(const char* username, float amount) {
    printf("\n=== Payment Processing ===\n");
    printf("Amount to pay: RM%.2f\n", amount);
    
    printf("\nSelect payment method:\n");
    printf("1. Credit/Debit Card\n");
    printf("2. Digital Wallet\n");
    printf("Choice: ");
    
    int choice;
    scanf("%d", &choice);
    
    if (choice < 1 || choice > PAYMENT_METHODS) {
        printf("Invalid payment method.\n");
        return 0;
    }
    
    PaymentMethod method = (PaymentMethod)(choice - 1);
    
    switch (method) {
        case PAYMENT_CARD: {
            CardDetails card;
            printf("\nEnter card number: ");
            scanf("%s", card.cardNumber);
            printf("Enter expiry date (MM/YY): ");
            scanf("%s", card.expiryDate);
            printf("Enter CVV: ");
            scanf("%s", card.cvv);
            
            if (strlen(card.cardNumber) < 16 || strlen(card.cvv) != 3) {
                printf("Invalid card details.\n");
                return 0;
            }
            
            printf("\nProcessing card payment...\n");
            break;
        }
        
        case PAYMENT_WALLET: {
            DigitalWallet wallet;
            printf("\nEnter wallet ID: ");
            scanf("%s", wallet.walletId);
            printf("Enter registered phone number: ");
            scanf("%s", wallet.phoneNumber);
            
            if (strlen(wallet.walletId) < 5 || strlen(wallet.phoneNumber) < 10) {
                printf("Invalid wallet details.\n");
                return 0;
            }
            
            printf("\nProcessing digital wallet payment...\n");
            break;
        }
    }
    
    printf("Payment of RM%.2f successful!\n", amount);
    
    char notifMsg[NOTIF_MSG_LEN];
    snprintf(notifMsg, NOTIF_MSG_LEN, "Payment of RM%.2f for ticket booking completed", amount);
    addNotification(username, notifMsg);
    
    return 1;
}

void notificationMenu() {
    int choice;
    do {
        showUserNotifications(current_user);
        
        printf("\n1. Mark as read\n");
        printf("2. Delete notification\n");
        printf("3. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 1 || choice == 2) {
            printf("Enter notification number: ");
            int notifNum;
            scanf("%d", &notifNum);
            
            if (choice == 1) {
                markNotificationAsRead(current_user, notifNum);
            } else {
                deleteNotification(current_user, notifNum);
            }
        }
    } while (choice != 3);
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

int main() {
    int choice;
    loadUsersFromFile();
    loadNotificationsFromFile();
    FILE *file = fopen("tickets.txt", "r");
    if (file) {
        while (fscanf(file, "%s %s %s %d", tickets[ticketCount].name, tickets[ticketCount].route,
                      tickets[ticketCount].time, &tickets[ticketCount].seatNumber) != EOF) {
            ticketCount++;
        }
        fclose(file);
    }

    while (1) {
        printf("\nMain Menu\n");
        printf("1. Register User\n");
        printf("2. Login\n");
        printf("3. View Profile\n");
        printf("4. Update Profile\n");
        printf("5. Add Frequent Route\n");
        printf("6. View Notifications\n");
        printf("7. Exit\n");
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
                        mainMenu();
                    }
                }
                break;
            case 3: viewProfile(); break;
            case 4: updateProfile(); break;
            case 5: addFrequentRoute(); break;
            case 6: notificationMenu(); break;
            case 7: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}