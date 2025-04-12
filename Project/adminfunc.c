#include <stdio.h>
#include <string.h>
#include "common.h"

void adminMainMenu() {
    char choice;
    while (1) {
        printf(
        "\n===== Admin Bus Reservation System =====\n"
        "1. Book a Ticket (Admin)\n"
        "2. View Schedule\n"
        "3. Cancel a Ticket (Admin)\n"
        "4. Manage Bus Schedules\n"
        "5. Generate Reports\n"
        "6. Exit to Main Menu\n"
        "==================================\n"
        "Enter choice: ");

        scanf(" %c", &choice);

        switch (choice) {
            case '1': adminBookTicket(); break;
            case '2': adminViewSchedule(); break;
            case '3': adminCancelTicket(); break;
            case '4': manageBusSchedules(); break;
            case '5': generateReports(); break;
            case '6': printf("Returning to main menu...\n"); return;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}

void adminBookTicket() {
    int routeChoice;
    adminViewSchedule();
    if (routeCount == 0) return;

    printf("\nEnter the route ID to book: ");
    scanf("%d", &routeChoice);
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
    printf("Booking successful! Seat number: %d\n", newTicket.seatNumber);
}

void adminViewSchedule() {
    printf("\nBus Schedules:\n");
    if (routeCount == 0) {
        printf("No schedules available.\n");
        return;
    }
    for (int i = 0; i < routeCount; i++) {
        printf("Bus ID: %d | Route: %s | Time: %s | Seats Available: %d\n",
               routes[i].id, routes[i].route, routes[i].time, routes[i].seatsAvailable);
    }
}

void adminCancelTicket() {
    int found = 0;
    printf("\n--- All Booked Tickets ---\n");
    for (int i = 0; i < ticketCount; i++) {
        printf("Ticket %d: User: %s | Route: %s | Time: %s | Seat No: %d\n",
               i + 1, tickets[i].name, tickets[i].route, tickets[i].time, tickets[i].seatNumber);
        found = 1;
    }
    if (!found) {
        printf("No tickets booked yet.\n");
        return;
    }

    printf("\nEnter ticket number to cancel (1-%d): ", ticketCount);
    int ticketNum;
    scanf("%d", &ticketNum);
    ticketNum--;

    if (ticketNum >= 0 && ticketNum < ticketCount) {
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
        printf("Invalid ticket number.\n");
    }
}

void manageBusSchedules() {
    char option;
    printf("\nManage Bus Schedules:\n1. Add\n2. Update\n3. Delete\nEnter choice: ");
    scanf(" %c", &option);

    if (option == '1' && routeCount < MAX_ROUTES) {
        printf("Enter Bus ID: ");
        scanf("%d", &routes[routeCount].id);
        printf("Enter Route: ");
        scanf(" %[^\n]", routes[routeCount].route);
        printf("Enter Time (e.g., 07:00 AM): ");
        scanf(" %[^\n]", routes[routeCount].time);
        printf("Enter Seats Available: ");
        scanf("%d", &routes[routeCount].seatsAvailable);
        routeCount++;
        printf("Schedule added!\n");
    } else if (option == '2') {
        int id, found = 0;
        printf("Enter Bus ID to update: ");
        scanf("%d", &id);
        for (int i = 0; i < routeCount; i++) {
            if (routes[i].id == id) {
                printf("Enter new Route: ");
                scanf(" %[^\n]", routes[i].route);
                printf("Enter new Time (e.g., 07:00 AM): ");
                scanf(" %[^\n]", routes[i].time);
                printf("Enter new Seats Available: ");
                scanf("%d", &routes[i].seatsAvailable);
                printf("Schedule updated!\n");
                found = 1;
                break;
            }
        }
        if (!found) printf("Bus ID not found!\n");
    } else if (option == '3') {
        int id, found = 0;
        printf("Enter Bus ID to delete: ");
        scanf("%d", &id);
        for (int i = 0; i < routeCount; i++) {
            if (routes[i].id == id) {
                routes[i] = routes[routeCount - 1];
                routeCount--;
                printf("Schedule deleted!\n");
                found = 1;
                break;
            }
        }
        if (!found) printf("Bus ID not found!\n");
    } else {
        printf("Invalid choice or storage full!\n");
    }
}

void generateReports() {
    printf("\nTotal Buses Scheduled: %d\n", routeCount);
    printf("Total Tickets Booked: %d\n", ticketCount);
    printf("\nBooking Details:\n");
    if (ticketCount == 0) {
        printf("No tickets booked yet.\n");
    } else {
        for (int i = 0; i < ticketCount; i++) {
            printf("User: %s | Route: %s | Time: %s | Seat No: %d\n",
                   tickets[i].name, tickets[i].route, tickets[i].time, tickets[i].seatNumber);
        }
    }
}