#ifndef COMMON_H
#define COMMON_H

#define MAX_FREQUENT_ROUTES 3
#define MAX_PAYMENT_METHODS 2
#define MAX_ROUTES 5
#define MAX_TICKETS 10
#define MAX_USERS 1000

typedef struct {
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

struct User {
    char username[50];
    char password[50];
    char email[50];    // New field
    char phone[15];    // New field
    char frequentRoutes[MAX_FREQUENT_ROUTES][50]; // Array of frequent routes
    char paymentMethods[MAX_PAYMENT_METHODS][50]; // Array of payment methods (e.g., "Visa ending 1234")
    int frequentRouteCount;
    int paymentMethodCount;
};

extern Route routes[MAX_ROUTES];
extern Ticket tickets[MAX_TICKETS];
extern int ticketCount;
extern struct User users[MAX_USERS];
extern int user_count;
extern char current_user[50];

// Ticket function declarations
void mainMenu();
void viewRoutes();
void bookTicket();
void cancelTicket();
void displayTickets();

#endif
