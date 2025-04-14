#ifndef COMMON_H
#define COMMON_H

#define MAX_ROUTES 5
#define MAX_TICKETS 10
#define MAX_USERS 100
#define MAX_FREQUENT_ROUTES 3
#define MAX_NOTIFICATIONS 50
#define NOTIF_MSG_LEN 100
#define PAYMENT_METHODS 2

#include <time.h>

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

struct User {
    char username[50];
    char password[50];
    char email[50];
    char phone[15];
    char frequentRoutes[MAX_FREQUENT_ROUTES][50];
    int frequentRouteCount;
    int isAdmin;
};

extern Route routes[MAX_ROUTES];
extern int routeCount;
extern Ticket tickets[MAX_TICKETS];
extern int ticketCount;
extern struct User users[MAX_USERS];
extern int user_count;
extern char current_user[50];
extern int current_user_is_admin;
extern Notification notifications[MAX_NOTIFICATIONS];
extern int notificationCount;

// Ticket function declarations (from ticket.c)
void mainMenu();
void viewRoutes();
void bookTicket();
void cancelTicket();
void displayTickets();

// Admin function declarations (from admin.c)
void adminMainMenu();
void adminBookTicket();
void adminViewSchedule();
void adminCancelTicket();
void manageBusSchedules();
void generateReports();
void notifyRouteChange(const char* action, const char* routeInfo);

// Notification and Payment function declarations (from login.c)
void addNotification(const char* username, const char* message);
void showUserNotifications(const char* username);
void markNotificationAsRead(const char* username, int index);
void deleteNotification(const char* username, int index);
void notificationMenu();
int processPayment(const char* username, float amount);

#endif