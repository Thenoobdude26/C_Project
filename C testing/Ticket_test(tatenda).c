// Please do not commit to this file, copy and edit on your device.
// and remember to check with everyone before pushing your changes.
// please.
// edited by: Tatenda
// edited on: 2025-03-19 18:19 

#include <stdio.h>
#include <string.h>

#define MAX_ROUTES 5
#define MAX_TICKETS 10

// Structure for routes
typedef struct {
    char route[50];
    char time[20];
    int seatsAvailable;
} Route;

// Structure for tickets
typedef struct {
    char name[50];
    char route[50];
    char time[20];
    int seatNumber;
} Ticket;

// Sample routes
Route routes[MAX_ROUTES] = {
    {"Maputo to Beira", "08:00 AM", 5},
    {"Beira to Nampula", "10:30 AM", 3},
    {"Nampula to Pemba", "01:00 PM", 4},
    {"Pemba to Maputo", "04:45 PM", 2},
    {"Maputo to Tete", "06:30 PM", 6}
};

// Booked tickets array
Ticket tickets[MAX_TICKETS];
int ticketCount = 0;

// Function prototypes
void mainMenu();
void searchRoutes();
void bookTicket();
void cancelTicket();
void displayTickets();

int main() {
    mainMenu();
    return 0;
}

// Main Menu
void mainMenu() {
    char choice;

    while (1) {
        printf(
"             ⠀⣀⣠⣤⣶⣶⣾⣿⣿⠛⠛⠿⢶⣦⣄⡀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⢛⣉⣉⡩⠤⣤⠄⠚⢃⣀⣴⢶⣦⡉⠻⢷⣤⡀\n"
"⠀⠀⣠⣤⣶⣶⣤⣤⣾⣯⠥⠴⠒⠒⠋⠉⠉⠉⠉⠉⢹⡏⠸⣟⡿⡶⠦⢌⡛⢷⣤⡀\n"
"⢀⡾⠋⣼⠿⢿⣶⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠁⢰⣟⢀⣰⠀⠀⠈⠙⣿⣿⣶⣄        \n"
"⣾⠇⢰⡏⠀⣼⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠤⣞⡇⠀⢸⠀⠀⠀⠀⡟⡆⠹⡿⣿⣦⣀     \n"
"⢹⣦⣾⠁⢰⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⠇⠀⢸⠀⠀⠀⠀⡇⡇⠀⡇⠀⢹⠻⣷⣤⡀ \n"
"⠀⠉⠁⠀⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢼⠀⠀⢸⠀⠀⠀⣰⢃⡗⠢⢥⡀⠀⡇⠘⡝⣿ \n"
"⠀⠀⠀⢸⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠸⠀⠀⢸⣀⠤⠚⠁⢸⡁⠀⠀⠈⠷⠗⠤⣇⣻⡇\n"
"⠀⠀⠀⣼⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠃⢠⡠⠔⢻⠁⢀⣀⠤⠴⡧⣀⣀⢀⠀⡆⠀⠀⢹⡇\n"
"⠀⠀⠀⣿⠳⠤⠤⢤⣀⠀⠀⠀⢀⣠⠤⠤⠤⠤⠔⠚⠁⠀⣠⡠⢤⣾⡯⠅⠒⠒⠒⡗⠒⠒⠼⠿⡷⠶⠶⢾⡇\n"
"⠀⠀⠀⣿⣦⣄⠀⠀⠈⠉⠉⠉⠉⠀⠀⠀⠀⣀⣠⣤⡶⠿⣷⠊⠁⢀⠃⠀⢠⠟⣦⡇⠀⠀⠀⠀⠃⡶⡄⢸⡇\n"
"⠀⠀⢸⣯⣈⣳⣭⣒⣤⣄⣀⣀⣤⣤⣶⣾⣽⣛⣉⣀⣀⡴⢻⠀⠀⠸⠀⠀⣿⡆⣹⡇⠀⠀⠀⡀⣆⡷⣧⣼⠇\n"
"⠀⠀⠈⣷⠆⢠⠇⠀⢨⡟⠿⠯⢭⠀⠀⠈⢆⠀⠀⢠⡄⠀⢸⠀⠀⠀⠆⠀⡿⡀⢿⣧⣤⣴⡶⠿⣯⣴⠏⠁⠀\n"
"⠀⠀⠀⠻⣶⣼⣦⣤⣤⣭⣭⣭⣭⣄⣀⣀⣈⣆⣀⣀⣀⣀⣼⣤⣤⡾⣶⡚⠁⢁⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠁⠀⠀⠀⠈⠙⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"     Welcome to the Bus Reservation System!       \n"
"==================================================\n"
"1. Search Routes & Schedules                      \n"
"2.  Book a Ticket                                 \n"
"3. Cancel a Ticket                                \n"
"4. View My Tickets                                \n"
"5. Exit                                           \n"
"==================================================\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                searchRoutes();
                break;
            case '2':
                bookTicket();
                break;
            case '3':
                cancelTicket();
                break;
            case '4':
                displayTickets();
                break;
            case '5':
                printf("Exiting... Have a great day!\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

// Function to search and display available routes
void searchRoutes() {
    printf("\n--- Available Routes & Schedules ---\n");
    for (int i = 0; i < MAX_ROUTES; i++) {
        printf("%d. Route: %s | Time: %s | Seats Available: %d\n",
               i + 1, routes[i].route, routes[i].time, routes[i].seatsAvailable);
    }
}

// Function to book a ticket
void bookTicket() {
    int routeChoice;
    char name[50];

    searchRoutes();  // Show available routes
    printf("\nEnter the route number to book: ");
    scanf("%d", &routeChoice);

    if (routeChoice < 1 || routeChoice > MAX_ROUTES || routes[routeChoice - 1].seatsAvailable == 0) {
        printf("Invalid choice or no seats available!\n");
        return;
    }

    printf("Enter your name: ");
    scanf(" %[^\n]", name);

    // Assign a seat and save the ticket
    Ticket newTicket;
    strcpy(newTicket.name, name);
    strcpy(newTicket.route, routes[routeChoice - 1].route);
    strcpy(newTicket.time, routes[routeChoice - 1].time);
    newTicket.seatNumber = routes[routeChoice - 1].seatsAvailable--;

    tickets[ticketCount++] = newTicket;

    printf("Booking successful! Your seat number is %d.\n", newTicket.seatNumber);
}

// Function to cancel a ticket
void cancelTicket() {
    char name[50];
    int found = 0;

    printf("\nEnter your name to cancel the ticket: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(tickets[i].name, name) == 0) {
            printf("Ticket for %s on route %s at %s canceled.\n", tickets[i].name, tickets[i].route, tickets[i].time);

            // Restore seat availability
            for (int j = 0; j < MAX_ROUTES; j++) {
                if (strcmp(routes[j].route, tickets[i].route) == 0) {
                    routes[j].seatsAvailable++;
                    break;
                }
            }

            // Shift tickets left in the array
            for (int j = i; j < ticketCount - 1; j++) {
                tickets[j] = tickets[j + 1];
            }
            ticketCount--;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No ticket found under this name.\n");
    }
}

// Function to display booked tickets
void displayTickets() {
    if (ticketCount == 0) {
        printf("\nNo tickets booked yet.\n");
        return;
    }

    printf("\n--- Your Booked Tickets ---\n");
    for (int i = 0; i < ticketCount; i++) {
        printf("Name: %s | Route: %s | Time: %s | Seat No: %d\n",
               tickets[i].name, tickets[i].route, tickets[i].time, tickets[i].seatNumber);
    }
}
