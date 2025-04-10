#ifndef COMMON_H
#define COMMON_H

#define MAX_ROUTES 5
#define MAX_TICKETS 10
#define MAX_USERS 100
#define MAX_FREQUENT_ROUTES 3

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
extern int routeCount;  // Added: Shared route count
extern Ticket tickets[MAX_TICKETS];
extern int ticketCount;
extern struct User users[MAX_USERS];
extern int user_count;
extern char current_user[50];

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

#endif