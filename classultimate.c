#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_ROUTES 5
#define MAX_TICKETS 10
#define MAX_USERS 100
#define MAX_FREQUENT_ROUTES 3
#define MAX_NOTIFICATIONS 50
#define NOTIF_MSG_LEN 100
#define PAYMENT_METHODS 2
#define TICKET_PRICE 20.0f

typedef struct {
    int id;
    char route[50];
    char time[20];
    int seatsAvailable;
} Route;

typedef struct {
    char name[50];
    char route[50];
    char time[20];
    int seatNumber;
} Ticket;

typedef struct {
    char username[50];
    char password[50];
    char email[50];
    char phone[15];
    char frequentRoutes[MAX_FREQUENT_ROUTES][50];
    int frequentRouteCount;
    int isAdmin;
} User;

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

// Global variables
Route routes[MAX_ROUTES];
int routeCount = 0;
Ticket tickets[MAX_TICKETS];
int ticketCount = 0;
User users[MAX_USERS];
int user_count = 0;
char current_user[50] = "";
int current_user_is_admin = 0;
Notification notifications[MAX_NOTIFICATIONS];
int notificationCount = 0;

// Function prototypes
void saveUsersToFile();
void loadUsersFromFile();
void registerUser();
int loginUser();
void viewProfile();
void updateProfile();
void addFrequentRoute();
void mainMenu();
void viewRoutes();
void bookTicket();
void cancelTicket();
void displayTickets();
void adminMainMenu();
void adminBookTicket();
void adminViewSchedule();
void adminCancelTicket();
void manageBusSchedules();
void generateReports();
void loadRoutesFromFile();
void saveRoutesToFile();
void loadTicketsFromFile();
void saveTicketsToFile();
void addNotification(const char* username, const char* message);
void showUserNotifications(const char* username);
void markNotificationAsRead(const char* username, int index);
void deleteNotification(const char* username, int index);
int processPayment(const char* username, float amount);
void notifyRouteChange(const char* action, const char* routeInfo);
void notificationMenu();
void bookTicketWithPayment();

// File Operations
void saveUsersToFile() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Error saving user data!\n");
        return;
    }
    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%s %s %s %s %d %d\n", 
                users[i].username, users[i].password,
                users[i].email, users[i].phone, 
                users[i].frequentRouteCount, users[i].isAdmin);
        for (int j = 0; j < users[i].frequentRouteCount; j++) {
            fprintf(file, "%s\n", users[i].frequentRoutes[j]);
        }
    }
    fclose(file);
}

void loadUsersFromFile() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) return;
    
    while (fscanf(file, "%s %s %s %s %d %d", 
                 users[user_count].username, users[user_count].password,
                 users[user_count].email, users[user_count].phone,
                 &users[user_count].frequentRouteCount, &users[user_count].isAdmin) != EOF) {
        for (int j = 0; j < users[user_count].frequentRouteCount; j++) {
            fscanf(file, "%s", users[user_count].frequentRoutes[j]);
        }
        user_count++;
        if (user_count >= MAX_USERS) break;
    }
    fclose(file);
}

void saveRoutesToFile() {
    FILE *file = fopen("routes.txt", "w");
    if (file == NULL) return;
    for (int i = 0; i < routeCount; i++) {
        fprintf(file, "%d %s %s %d\n", 
                routes[i].id, routes[i].route, 
                routes[i].time, routes[i].seatsAvailable);
    }
    fclose(file);
}

void loadRoutesFromFile() {
    FILE *file = fopen("routes.txt", "r");
    if (file == NULL) return;
    
    while (fscanf(file, "%d %49[^\n] %19[^\n] %d", 
                 &routes[routeCount].id, routes[routeCount].route,
                 routes[routeCount].time, &routes[routeCount].seatsAvailable) != EOF) {
        routeCount++;
        if (routeCount >= MAX_ROUTES) break;
    }
    fclose(file);
}

void saveTicketsToFile() {
    FILE *file = fopen("tickets.txt", "w");
    if (file == NULL) return;
    for (int i = 0; i < ticketCount; i++) {
        fprintf(file, "%s %s %s %d\n", 
                tickets[i].name, tickets[i].route,
                tickets[i].time, tickets[i].seatNumber);
    }
    fclose(file);
}

void loadTicketsFromFile() {
    FILE *file = fopen("tickets.txt", "r");
    if (file == NULL) return;
    
    while (fscanf(file, "%s %s %s %d", 
                 tickets[ticketCount].name, tickets[ticketCount].route,
                 tickets[ticketCount].time, &tickets[ticketCount].seatNumber) != EOF) {
        ticketCount++;
        if (ticketCount >= MAX_TICKETS) break;
    }
    fclose(file);
}

// Notification System
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
    printf("Notification deleted.\n");
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

// Payment System
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

void notifyRouteChange(const char* action, const char* routeInfo) {
    for (int i = 0; i < user_count; i++) {
        char notifMsg[NOTIF_MSG_LEN];
        snprintf(notifMsg, NOTIF_MSG_LEN, "Route %s: %s", action, routeInfo);
        addNotification(users[i].username, notifMsg);
    }
}

// User Management
void registerUser() {
    if (user_count >= MAX_USERS) {
        printf("User limit reached!\n");
        return;
    }
    
    printf("\n--- Register New User ---\n");
    printf("Username: ");
    scanf("%s", users[user_count].username);
    printf("Password: ");
    scanf("%s", users[user_count].password);
    printf("Email: ");
    scanf("%s", users[user_count].email);
    printf("Phone: ");
    scanf("%s", users[user_count].phone);
    printf("Admin (1) or Regular (0): ");
    scanf("%d", &users[user_count].isAdmin);
    
    users[user_count].frequentRouteCount = 0;
    user_count++;
    saveUsersToFile();
    
    char notifMsg[NOTIF_MSG_LEN];
    snprintf(notifMsg, NOTIF_MSG_LEN, "Welcome to the Bus Reservation System!");
    addNotification(users[user_count-1].username, notifMsg);
    
    printf("Registration successful!\n");
}

int loginUser() {
    char username[50], password[50];
    printf("\n--- Login ---\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && 
            strcmp(users[i].password, password) == 0) {
            strcpy(current_user, username);
            current_user_is_admin = users[i].isAdmin;
            return 1;
        }
    }
    printf("Invalid credentials!\n");
    return 0;
}

void viewProfile() {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, current_user) == 0) {
            printf("\n--- Your Profile ---\n");
            printf("Username: %s\n", users[i].username);
            printf("Email: %s\n", users[i].email);
            printf("Phone: %s\n", users[i].phone);
            printf("Account Type: %s\n", users[i].isAdmin ? "Admin" : "Regular");
            
            printf("\nFrequent Routes:\n");
            if (users[i].frequentRouteCount == 0) {
                printf("None saved\n");
            } else {
                for (int j = 0; j < users[i].frequentRouteCount; j++) {
                    printf("%d. %s\n", j+1, users[i].frequentRoutes[j]);
                }
            }
            return;
        }
    }
    printf("Profile not found!\n");
}

void updateProfile() {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, current_user) == 0) {
            printf("\n--- Update Profile ---\n");
            printf("New email (current: %s): ", users[i].email);
            char newEmail[50];
            scanf(" %[^\n]", newEmail);
            if (strlen(newEmail) > 0) strcpy(users[i].email, newEmail);
            
            printf("New phone (current: %s): ", users[i].phone);
            char newPhone[15];
            scanf(" %[^\n]", newPhone);
            if (strlen(newPhone) > 0) strcpy(users[i].phone, newPhone);
            
            saveUsersToFile();
            
            char notifMsg[NOTIF_MSG_LEN] = "Your profile has been updated";
            addNotification(current_user, notifMsg);
            
            printf("Profile updated!\n");
            return;
        }
    }
    printf("User not found!\n");
}

void addFrequentRoute() {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, current_user) == 0) {
            if (users[i].frequentRouteCount >= MAX_FREQUENT_ROUTES) {
                printf("Frequent route limit reached!\n");
                return;
            }
            
            printf("Enter route to add: ");
            scanf(" %[^\n]", users[i].frequentRoutes[users[i].frequentRouteCount]);
            users[i].frequentRouteCount++;
            saveUsersToFile();
            
            char notifMsg[NOTIF_MSG_LEN];
            snprintf(notifMsg, NOTIF_MSG_LEN, "Added frequent route: %s", 
                    users[i].frequentRoutes[users[i].frequentRouteCount-1]);
            addNotification(current_user, notifMsg);
            
            printf("Route added to favorites!\n");
            return;
        }
    }
    printf("User not found!\n");
}

// Regular User Functions
void mainMenu() {
    char choice;
    while (1) {
        printf("\n=== User Menu ===\n");
        printf("1. View Routes\n");
        printf("2. Book Ticket\n");
        printf("3. Cancel Ticket\n");
        printf("4. View Tickets\n");
        printf("5. View Profile\n");
        printf("6. Update Profile\n");
        printf("7. Add Frequent Route\n");
        printf("8. Notifications\n");
        printf("9. Logout\n");
        printf("Choice: ");
        scanf(" %c", &choice);
        
        switch (choice) {
            case '1': viewRoutes(); break;
            case '2': bookTicketWithPayment(); break;
            case '3': cancelTicket(); break;
            case '4': displayTickets(); break;
            case '5': viewProfile(); break;
            case '6': updateProfile(); break;
            case '7': addFrequentRoute(); break;
            case '8': notificationMenu(); break;
            case '9': return;
            default: printf("Invalid choice!\n");
        }
    }
}

void viewRoutes() {
    printf("\n--- Available Routes ---\n");
    if (routeCount == 0) {
        printf("No routes available!\n");
        return;
    }
    
    for (int i = 0; i < routeCount; i++) {
        printf("%d. %s | %s | Seats: %d\n", 
               routes[i].id, routes[i].route, 
               routes[i].time, routes[i].seatsAvailable);
    }
}

void bookTicketWithPayment() {
    viewRoutes();
    if (routeCount == 0) return;
    
    printf("\nEnter route ID to book: ");
    int routeId;
    scanf("%d", &routeId);
    
    int routeIndex = -1;
    for (int i = 0; i < routeCount; i++) {
        if (routes[i].id == routeId) {
            routeIndex = i;
            break;
        }
    }
    
    if (routeIndex == -1) {
        printf("Invalid route ID!\n");
        return;
    }
    
    if (routes[routeIndex].seatsAvailable <= 0) {
        printf("No seats available!\n");
        return;
    }
    
    if (!processPayment(current_user, TICKET_PRICE)) {
        printf("Payment failed. Booking cancelled.\n");
        return;
    }
    
    Ticket newTicket;
    strcpy(newTicket.name, current_user);
    strcpy(newTicket.route, routes[routeIndex].route);
    strcpy(newTicket.time, routes[routeIndex].time);
    newTicket.seatNumber = routes[routeIndex].seatsAvailable;
    
    routes[routeIndex].seatsAvailable--;
    tickets[ticketCount++] = newTicket;
    saveTicketsToFile();
    saveRoutesToFile();
    
    char notifMsg[NOTIF_MSG_LEN];
    snprintf(notifMsg, NOTIF_MSG_LEN, "Ticket booked for %s at %s (Seat: %d)", 
            routes[routeIndex].route, routes[routeIndex].time, newTicket.seatNumber);
    addNotification(current_user, notifMsg);
    
    printf("Ticket booked! Seat: %d\n", newTicket.seatNumber);
}

void cancelTicket() {
    int userTickets = 0;
    printf("\n--- Your Tickets ---\n");
    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(tickets[i].name, current_user) == 0) {
            printf("%d. %s | %s | Seat: %d\n", 
                   userTickets+1, tickets[i].route, 
                   tickets[i].time, tickets[i].seatNumber);
            userTickets++;
        }
    }
    
    if (userTickets == 0) {
        printf("No tickets found!\n");
        return;
    }
    
    printf("Enter ticket number to cancel: ");
    int ticketNum;
    scanf("%d", &ticketNum);
    
    if (ticketNum < 1 || ticketNum > userTickets) {
        printf("Invalid ticket number!\n");
        return;
    }
    
    int found = 0;
    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(tickets[i].name, current_user) == 0) {
            found++;
            if (found == ticketNum) {
                for (int j = 0; j < routeCount; j++) {
                    if (strcmp(routes[j].route, tickets[i].route) == 0) {
                        routes[j].seatsAvailable++;
                        break;
                    }
                }
                
                for (int j = i; j < ticketCount-1; j++) {
                    tickets[j] = tickets[j+1];
                }
                ticketCount--;
                
                saveTicketsToFile();
                saveRoutesToFile();
                
                char notifMsg[NOTIF_MSG_LEN];
                snprintf(notifMsg, NOTIF_MSG_LEN, "Ticket canceled for %s", tickets[i].route);
                addNotification(current_user, notifMsg);
                
                printf("Ticket canceled!\n");
                return;
            }
        }
    }
}

void displayTickets() {
    printf("\n--- Your Tickets ---\n");
    int found = 0;
    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(tickets[i].name, current_user) == 0) {
            printf("%d. %s | %s | Seat: %d\n", 
                   found+1, tickets[i].route, 
                   tickets[i].time, tickets[i].seatNumber);
            found++;
        }
    }
    
    if (found == 0) {
        printf("No tickets found!\n");
    }
}

// Admin Functions
void adminMainMenu() {
    char choice;
    while (1) {
        printf("\n=== Admin Menu ===\n");
        printf("1. Manage Routes\n");
        printf("2. View All Tickets\n");
        printf("3. Generate Reports\n");
        printf("4. Notifications\n");
        printf("5. Logout\n");
        printf("Choice: ");
        scanf(" %c", &choice);
        
        switch (choice) {
            case '1': manageBusSchedules(); break;
            case '2': adminViewSchedule(); break;
            case '3': generateReports(); break;
            case '4': notificationMenu(); break;
            case '5': return;
            default: printf("Invalid choice!\n");
        }
    }
}

void manageBusSchedules() {
    char choice;
    while (1) {
        printf("\n=== Route Management ===\n");
        printf("1. Add Route\n");
        printf("2. Update Route\n");
        printf("3. Delete Route\n");
        printf("4. View Routes\n");
        printf("5. Back\n");
        printf("Choice: ");
        scanf(" %c", &choice);
        
        switch (choice) {
            case '1': 
                if (routeCount >= MAX_ROUTES) {
                    printf("Route limit reached!\n");
                    break;
                }
                printf("Enter route ID: ");
                scanf("%d", &routes[routeCount].id);
                printf("Enter route: ");
                scanf(" %[^\n]", routes[routeCount].route);
                printf("Enter time: ");
                scanf(" %[^\n]", routes[routeCount].time);
                printf("Enter seats: ");
                scanf("%d", &routes[routeCount].seatsAvailable);
                
                char notifMsg[NOTIF_MSG_LEN];
                snprintf(notifMsg, NOTIF_MSG_LEN, "New route: %s at %s", 
                        routes[routeCount].route, routes[routeCount].time);
                notifyRouteChange("added", notifMsg);
                
                routeCount++;
                saveRoutesToFile();
                printf("Route added!\n");
                break;
            case '2': {
                printf("Enter route ID to update: ");
                int id;
                scanf("%d", &id);
                int found = 0;
                for (int i = 0; i < routeCount; i++) {
                    if (routes[i].id == id) {
                        printf("New route (current: %s): ", routes[i].route);
                        scanf(" %[^\n]", routes[i].route);
                        printf("New time (current: %s): ", routes[i].time);
                        scanf(" %[^\n]", routes[i].time);
                        printf("New seats (current: %d): ", routes[i].seatsAvailable);
                        scanf("%d", &routes[i].seatsAvailable);
                        
                        char notifMsg[NOTIF_MSG_LEN];
                        snprintf(notifMsg, NOTIF_MSG_LEN, "Updated route: %s at %s", 
                                routes[i].route, routes[i].time);
                        notifyRouteChange("updated", notifMsg);
                        
                        saveRoutesToFile();
                        printf("Route updated!\n");
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("Route not found!\n");
                break;
            }
            case '3': {
                printf("Enter route ID to delete: ");
                int id;
                scanf("%d", &id);
                int found = 0;
                for (int i = 0; i < routeCount; i++) {
                    if (routes[i].id == id) {
                        char notifMsg[NOTIF_MSG_LEN];
                        snprintf(notifMsg, NOTIF_MSG_LEN, "Deleted route: %s at %s", 
                                routes[i].route, routes[i].time);
                        notifyRouteChange("removed", notifMsg);
                        
                        routes[i] = routes[routeCount-1];
                        routeCount--;
                        saveRoutesToFile();
                        printf("Route deleted!\n");
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("Route not found!\n");
                break;
            }
            case '4': 
                viewRoutes(); 
                break;
            case '5': 
                return;
            default: 
                printf("Invalid choice!\n");
        }
    }
}

void adminViewSchedule() {
    printf("\n--- All Bookings ---\n");
    if (ticketCount == 0) {
        printf("No bookings found!\n");
        return;
    }
    
    for (int i = 0; i < ticketCount; i++) {
        printf("%d. %s | %s | %s | Seat: %d\n", 
               i+1, tickets[i].name, tickets[i].route,
               tickets[i].time, tickets[i].seatNumber);
    }
}

void generateReports() {
    printf("\n=== System Report ===\n");
    printf("Total Users: %d\n", user_count);
    printf("Total Routes: %d\n", routeCount);
    printf("Total Bookings: %d\n", ticketCount);
    
    printf("\nRoute Occupancy:\n");
    for (int i = 0; i < routeCount; i++) {
        int bookings = 0;
        for (int j = 0; j < ticketCount; j++) {
            if (strcmp(tickets[j].route, routes[i].route) == 0) {
                bookings++;
            }
        }
        printf("%s: %d/%d seats booked\n", 
               routes[i].route, bookings, 
               bookings + routes[i].seatsAvailable);
    }
}

// Main Program
int main() {
    loadUsersFromFile();
    loadRoutesFromFile();
    loadTicketsFromFile();
    
    int choice;
    while (1) {
        printf("\n=== Bus Reservation System ===\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: 
                if (loginUser()) {
                    printf("\nWelcome, %s!\n", current_user);
                    if (current_user_is_admin) {
                        adminMainMenu();
                    } else {
                        mainMenu();
                    }
                }
                break;
            case 2: 
                registerUser(); 
                break;
            case 3: 
                printf("Exiting...\n");
                return 0;
            default: 
                printf("Invalid choice!\n");
        }
    }
}