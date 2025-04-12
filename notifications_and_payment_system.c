#include <stdio.h>
#include <string.h>
#include <time.h>
// goodluck T , call me if you need help i already integrated it into the big code thing i made and it worked just fine there is a global variable in my code, 
//get rid of them and edit accordingly. 
// The global variables in this code are:
// 1. notifications[MAX_NOTIFICATIONS] - Array to store notifications.
// 2. notificationCount - Integer to track the number of notifications.
// i do not know if there are more , stay vigilant. 
#define MAX_NOTIFICATIONS 50
#define NOTIF_MSG_LEN 100
#define PAYMENT_METHODS 2

typedef struct {
    char username[50];
    char message[NOTIF_MSG_LEN];
    time_t timestamp;
    int isRead;
} Notification;

typedef struct {
    char cardNumber[20];
    char expiryDate[10];
    char cvv[5];
} CardDetails;

typedef struct {
    char walletId[20];
    char phoneNumber[15];
} DigitalWallet;

typedef enum {
    PAYMENT_CARD,
    PAYMENT_WALLET
} PaymentMethod;

Notification notifications[MAX_NOTIFICATIONS];
int notificationCount = 0;

// Notification System Functions
void addNotification(const char* username, const char* message) {
    if (notificationCount >= MAX_NOTIFICATIONS) {
        // Remove oldest notification if we're at capacity
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
    
    // Find the notification to delete
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
    
    // Shift all notifications after this one
    for (int i = toDelete; i < notificationCount - 1; i++) {
        notifications[i] = notifications[i + 1];
    }
    
    notificationCount--;
    printf("Notification deleted.\n");
}

// Payment System Functions
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
            
            // Validate card details (theoretical)
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
            
            // Validate wallet details (theoretical)
            if (strlen(wallet.walletId) < 5 || strlen(wallet.phoneNumber) < 10) {
                printf("Invalid wallet details.\n");
                return 0;
            }
            
            printf("\nProcessing digital wallet payment...\n");
            break;
        }
    }
    
    // Simulate payment processing
    printf("Payment of RM%.2f successful!\n", amount);
    
    // Add payment confirmation notification
    char notifMsg[NOTIF_MSG_LEN];
    snprintf(notifMsg, NOTIF_MSG_LEN, "Payment of RM%.2f for ticket booking completed", amount);
    addNotification(username, notifMsg);
    
    return 1;
}

// Utility function to notify about route changes
void notifyRouteChange(const char* action, const char* routeInfo) {
    // Notify all users (in a real system, you might want to notify only interested users)
    for (int i = 0; i < user_count; i++) {
        char notifMsg[NOTIF_MSG_LEN];
        snprintf(notifMsg, NOTIF_MSG_LEN, "Route %s: %s", action, routeInfo);
        addNotification(users[i].username, notifMsg);
    }
}

// Example usage in your existing functions:
// When booking a ticket (replace your existing bookTicket function):
void bookTicketWithPayment() {
    // ... your existing booking logic ...
    
    // Process payment
    float ticketPrice = 20.0f; // RM20 per ticket
    if (!processPayment(current_user, ticketPrice)) {
        printf("Payment failed. Booking cancelled.\n");
        return;
    }
    
    // ... rest of your booking logic ...
}

// When admin adds/changes/deletes routes:
void adminManageRoutes() {
    // ... your existing route management ...
    
    // After adding a route:
    // notifyRouteChange("added", newRouteInfo);
    
    // After changing a route:
    // notifyRouteChange("updated", updatedRouteInfo);
    
    // After deleting a route:
    // notifyRouteChange("removed", deletedRouteInfo);
}

// Add this to your user menu:
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
