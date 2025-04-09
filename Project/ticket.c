#include <stdio.h>
#include <string.h>
#include "common.h"

Route routes[MAX_ROUTES] = {
    {"KL to Penang", "07:00 AM", 5},
    {"KL to Johor Bahru", "09:30 AM", 3},
    {"KL to Kuantan", "12:00 PM", 4},
    {"KL to Ipoh", "03:30 PM", 2},
    {"KL to Melaka", "06:00 PM", 6}
};
Ticket tickets[MAX_TICKETS];
int ticketCount = 0;

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
"1. View Routes & Schedules                      \n"
"2. Book a Ticket                                 \n"
"3. Cancel a Ticket                                \n"
"4. View My Tickets                                \n"
"5. Exit                                           \n"
"==================================================\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1': viewRoutes(); break;
            case '2': bookTicket(); break;
            case '3': cancelTicket(); break;
            case '4': displayTickets(); break;
            case '5': printf("Exiting... Have a great day!\n"); return;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

void viewRoutes() {
    printf("\n--- Available Routes & Schedules ---\n");
    for (int i = 0; i < MAX_ROUTES; i++) {
        printf("%d. Route: %s | Time: %s | Seats Available: %d\n",
               i + 1, routes[i].route, routes[i].time, routes[i].seatsAvailable);
    }
}

void bookTicket() {
    int routeChoice;
    viewRoutes();
    printf("\nEnter the route number to book: ");
    scanf("%d", &routeChoice);

    if (routeChoice < 1 || routeChoice > MAX_ROUTES || routes[routeChoice - 1].seatsAvailable == 0) {
        printf("Invalid choice or no seats available!\n");
        return;
    }

    Ticket newTicket;
    strcpy(newTicket.name, current_user); // Use authenticated user
    strcpy(newTicket.route, routes[routeChoice - 1].route);
    strcpy(newTicket.time, routes[routeChoice - 1].time);
    newTicket.seatNumber = routes[routeChoice - 1].seatsAvailable--;

    tickets[ticketCount++] = newTicket;
    printf("Booking successful! Your seat number is %d.\n", newTicket.seatNumber);
}

void cancelTicket() {
    int found = 0;
    displayTickets();
    printf("\nEnter ticket number to cancel (1-%d): ", ticketCount);
    int ticketNum;
    scanf("%d", &ticketNum);
    ticketNum--;

    if (ticketNum >= 0 && ticketNum < ticketCount && strcmp(tickets[ticketNum].name, current_user) == 0) {
        printf("Ticket for %s on route %s at %s canceled.\n", 
               tickets[ticketNum].name, tickets[ticketNum].route, tickets[ticketNum].time);
        for (int j = 0; j < MAX_ROUTES; j++) {
            if (strcmp(routes[j].route, tickets[ticketNum].route) == 0) {
                routes[j].seatsAvailable++;
                break;
            }
        }
        for (int j = ticketNum; j < ticketCount - 1; j++) {
            tickets[j] = tickets[j + 1];
        }
        ticketCount--;
        found = 1;
    }
    if (!found) {
        printf("No ticket found under your account or invalid ticket number.\n");
    }
}

void displayTickets() {
    int found = 0;
    printf("\n--- Your Booked Tickets ---\n");
    for (int i = 0; i < ticketCount; i++) {
        if (strcmp(tickets[i].name, current_user) == 0) {
            printf("Ticket %d: Route: %s | Time: %s | Seat No: %d\n",
                   i + 1, tickets[i].route, tickets[i].time, tickets[i].seatNumber);
            found = 1;
        }
    }
    if (!found) {
        printf("No tickets booked yet under your account.\n");
    }
}