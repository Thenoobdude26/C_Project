#include <stdio.h>
#include <string.h>
#include "common.h"

Route routes[MAX_ROUTES];
int routeCount = 0;  // Define here (shared with admin.c)
Ticket tickets[MAX_TICKETS];
int ticketCount = 0;

void mainMenu() {
    char choice;
    while (1) {
        printf(
"     Welcome to the Bus Reservation System!       \n"
"==================================================\n"
"1. View Routes & Schedules                      \n"
"2. Book a Ticket                                 \n"
"3. Cancel a Ticket                                \n"
"4. View My Tickets                                \n"
"5. Exit to Main Menu                             \n"
"==================================================\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1': viewRoutes(); break;
            case '2': bookTicket(); break;
            case '3': cancelTicket(); break;
            case '4': displayTickets(); break;
            case '5': printf("Returning to main menu...\n"); return;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

void viewRoutes() {
    printf("\n--- Available Routes & Schedules ---\n");
    if (routeCount == 0) {
        printf("No routes available. Please contact an admin to add routes.\n");
        return;
    }
    for (int i = 0; i < routeCount; i++) {
        printf("Bus ID: %d | Route: %s | Time: %s | Seats Available: %d\n",
               routes[i].id, routes[i].route, routes[i].time, routes[i].seatsAvailable);
    }
}

void bookTicket() {
    int routeChoice;
    int userIndex = -1;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, current_user) == 0) {
            userIndex = i;
            break;
        }
    }

    if (userIndex != -1 && users[userIndex].frequentRouteCount > 0) {
        printf("\nYour Frequent Routes:\n");
        for (int i = 0; i < users[userIndex].frequentRouteCount; i++) {
            printf("%d. %s\n", i + 1, users[userIndex].frequentRoutes[i]);
        }
        printf("0. Choose from all routes\n");
        printf("Select a frequent route (or 0): ");
        scanf("%d", &routeChoice);
        if (routeChoice > 0 && routeChoice <= users[userIndex].frequentRouteCount) {
            for (int i = 0; i < routeCount; i++) {
                if (strcmp(routes[i].route, users[userIndex].frequentRoutes[routeChoice - 1]) == 0) {
                    routeChoice = routes[i].id;
                    break;
                }
            }
        } else {
            routeChoice = 0;
        }
    } else {
        routeChoice = 0;
    }

    if (routeChoice == 0) {
        viewRoutes();
        if (routeCount == 0) return;
        printf("\nEnter the route ID to book: ");
        scanf("%d", &routeChoice);
    }

    int routeIndex = -1;
    for (int i = 0; i < routeCount; i++) {
        if (routes[i].id == routeChoice) {
            routeIndex = i;
            break;
        }
    }

    if (routeIndex == -1 || routes[routeIndex].seatsAvailable == 0) {
        printf("Invalid route ID or no seats available!\n");
        return;
    }

    Ticket newTicket;
    strcpy(newTicket.name, current_user);
    strcpy(newTicket.route, routes[routeIndex].route);
    strcpy(newTicket.time, routes[routeIndex].time);
    newTicket.seatNumber = routes[routeIndex].seatsAvailable--;

    tickets[ticketCount++] = newTicket;
    FILE *file = fopen("tickets.txt", "w");
    if (file) {
        for (int i = 0; i < ticketCount; i++) {
            fprintf(file, "%s %s %s %d\n", tickets[i].name, tickets[i].route, tickets[i].time, tickets[i].seatNumber);
        }
        fclose(file);
    }
    printf("Booking successful! Your seat number is %d.\n", newTicket.seatNumber);
}

void cancelTicket() {
    int found = 0;
    displayTickets();
    if (ticketCount == 0) return;

    printf("\nEnter ticket number to cancel (1-%d): ", ticketCount);
    int ticketNum;
    scanf("%d", &ticketNum);
    ticketNum--;

    if (ticketNum >= 0 && ticketNum < ticketCount && strcmp(tickets[ticketNum].name, current_user) == 0) {
        printf("Ticket for %s on route %s at %s canceled.\n", 
               tickets[ticketNum].name, tickets[ticketNum].route, tickets[ticketNum].time);
        for (int j = 0; j < routeCount; j++) {
            if (strcmp(routes[j].route, tickets[ticketNum].route) == 0) {
                routes[j].seatsAvailable++;
                break;
            }
        }
        for (int j = ticketNum; j < ticketCount - 1; j++) {
            tickets[j] = tickets[j + 1];
        }
        ticketCount--;
        FILE *file = fopen("tickets.txt", "w");
        if (file) {
            for (int i = 0; i < ticketCount; i++) {
                fprintf(file, "%s %s %s %d\n", tickets[i].name, tickets[i].route, tickets[i].time, tickets[i].seatNumber);
            }
            fclose(file);
        }
        printf("Ticket canceled successfully!\n");
    } else {
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