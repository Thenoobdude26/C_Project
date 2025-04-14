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

    float ticketPrice = 20.0f;
    if (!processPayment(current_user, ticketPrice)) {
        printf("Payment failed. Booking cancelled.\n");
        return;
    }

    Ticket newTicket;
    strcpy(newTicket.name, current_user);
    strcpy(newTicket.route, routes[routeIndex].route);
    strcpy(newTicket.time, routes[routeIndex].time);
    newTicket.seatNumber = routes[routeIndex].seatsAvailable--;

    tickets[ticketCount++] = newTicket;
    FILE *file = fopen("tickets.txt", "w");
    if (file == NULL) {
        printf("Error saving tickets to file!\n");
        return;
    }
    for (int i = 0; i < ticketCount; i++) {
        fprintf(file, "%s %s %s %d\n", tickets[i].name, tickets[i].route, tickets[i].time, tickets[i].seatNumber);
    }
    fclose(file);
    // Save updated seats
    FILE *routeFile = fopen("routes.txt", "w");
    if (routeFile == NULL) {
        printf("Error saving routes to file!\n");
        return;
    }
    for (int i = 0; i < routeCount; i++) {
        fprintf(routeFile, "%d %s %s %d\n", routes[i].id, routes[i].route, routes[i].time, routes[i].seatsAvailable);
    }
    fclose(routeFile);
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
        char notifMsg[NOTIF_MSG_LEN];
        snprintf(notifMsg, NOTIF_MSG_LEN, "Ticket for route %s at %s canceled by admin", 
                 tickets[ticketNum].route, tickets[ticketNum].time);
        addNotification(tickets[ticketNum].name, notifMsg);
        for (int j = ticketNum; j < ticketCount - 1; j++) {
            tickets[j] = tickets[j + 1];
        }
        ticketCount--;
        FILE *file = fopen("tickets.txt", "w");
        if (file == NULL) {
            printf("Error saving tickets to file!\n");
            return;
        }
        for (int i = 0; i < ticketCount; i++) {
            fprintf(file, "%s %s %s %d\n", tickets[i].name, tickets[i].route, tickets[i].time, tickets[i].seatNumber);
        }
        fclose(file);
        // Save updated seats
        FILE *routeFile = fopen("routes.txt", "w");
        if (routeFile == NULL) {
            printf("Error saving routes to file!\n");
            return;
        }
        for (int i = 0; i < routeCount; i++) {
            fprintf(routeFile, "%d %s %s %d\n", routes[i].id, routes[i].route, routes[i].time, routes[i].seatsAvailable);
        }
        fclose(routeFile);
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
        getchar();  // Clear newline
        printf("Enter Route: ");
        scanf("%[^\n]", routes[routeCount].route);
        getchar();
        printf("Enter Time (e.g., 07:00 AM): ");
        scanf("%[^\n]", routes[routeCount].time);
        getchar();
        printf("Enter Seats Available: ");
        scanf("%d", &routes[routeCount].seatsAvailable);
        char routeInfo[NOTIF_MSG_LEN];
        snprintf(routeInfo, NOTIF_MSG_LEN, "%s at %s", routes[routeCount].route, routes[routeCount].time);
        routeCount++;
        notifyRouteChange("added", routeInfo);
        // Save routes
        FILE *file = fopen("routes.txt", "w");
        if (file == NULL) {
            printf("Error saving routes to file!\n");
            return;
        }
        for (int i = 0; i < routeCount; i++) {
            fprintf(file, "%d %s %s %d\n", routes[i].id, routes[i].route, routes[i].time, routes[i].seatsAvailable);
        }
        fclose(file);
        printf("Schedule added!\n");
    } else if (option == '2') {
        int id, found = 0;
        printf("Enter Bus ID to update: ");
        scanf("%d", &id);
        for (int i = 0; i < routeCount; i++) {
            if (routes[i].id == id) {
                getchar();
                printf("Enter new Route: ");
                scanf("%[^\n]", routes[i].route);
                getchar();
                printf("Enter new Time (e.g., 07:00 AM): ");
                scanf("%[^\n]", routes[i].time);
                getchar();
                printf("Enter new Seats Available: ");
                scanf("%d", &routes[i].seatsAvailable);
                char routeInfo[NOTIF_MSG_LEN];
                snprintf(routeInfo, NOTIF_MSG_LEN, "%s at %s", routes[i].route, routes[i].time);
                notifyRouteChange("updated", routeInfo);
                // Save routes
                FILE *file = fopen("routes.txt", "w");
                if (file == NULL) {
                    printf("Error saving routes to file!\n");
                    return;
                }
                for (int i = 0; i < routeCount; i++) {
                    fprintf(file, "%d %s %s %d\n", routes[i].id, routes[i].route, routes[i].time, routes[i].seatsAvailable);
                }
                fclose(file);
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
                char routeInfo[NOTIF_MSG_LEN];
                snprintf(routeInfo, NOTIF_MSG_LEN, "%s at %s", routes[i].route, routes[i].time);
                routes[i] = routes[routeCount - 1];
                routeCount--;
                notifyRouteChange("removed", routeInfo);
                // Save routes
                FILE *file = fopen("routes.txt", "w");
                if (file == NULL) {
                    printf("Error saving routes to file!\n");
                    return;
                }
                for (int i = 0; i < routeCount; i++) {
                    fprintf(file, "%d %s %s %d\n", routes[i].id, routes[i].route, routes[i].time, routes[i].seatsAvailable);
                }
                fclose(file);
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

void notifyRouteChange(const char* action, const char* routeInfo) {
    for (int i = 0; i < user_count; i++) {
        char notifMsg[NOTIF_MSG_LEN];
        snprintf(notifMsg, NOTIF_MSG_LEN, "Route %s: %s", action, routeInfo);
        addNotification(users[i].username, notifMsg);
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