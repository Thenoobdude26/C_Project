#include <stdio.h>
#include <string.h>

// Constants and global variables
#define MAX_USERS 100
#define MAX_ROUTES 50
#define MAX_TICKETS 100
#define MAX_FREQUENT_ROUTES 10

typedef struct {
    char username[50];
    char password[50];
    char email[50];
    char phone[15];
    int frequentRouteCount;
    char frequentRoutes[MAX_FREQUENT_ROUTES][50];
    int isAdmin;
} User;

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

User users[MAX_USERS];
Route routes[MAX_ROUTES];
Ticket tickets[MAX_TICKETS];
int user_count = 0, routeCount = 0, ticketCount = 0;
char current_user[50];
int current_user_is_admin = 0;

// Function prototypes
void loadUsersFromFile();
void saveUsersToFile();
void registerUser();
int loginUser();
void viewProfile();
void updateProfile();
void addFrequentRoute();
void mainMenu();
void adminMainMenu();
void viewRoutes();
void bookTicket();
void cancelTicket();
void displayTickets();
void adminBookTicket();
void adminViewSchedule();
void adminCancelTicket();
void manageBusSchedules();
void generateReports();

// Main function
int main() {
    int choice;
    loadUsersFromFile();

    FILE *file = fopen("tickets.txt", "r");
    if (file) {
        while (fscanf(file, "%s %s %s %d", tickets[ticketCount].name, tickets[ticketCount].route,
                      tickets[ticketCount].time, &tickets[ticketCount].seatNumber) != EOF) {
            ticketCount++;
        }
        fclose(file);
    }

    while (1) {
        printf("\nMain Menu\n");
        printf("1. Register User\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: registerUser(); break;
            case 2:
                if (loginUser()) {
                    printf("Welcome, %s!\n", current_user);
                    if (current_user_is_admin) {
                        printf("You are logged in as an admin.\n");
                        adminMainMenu();
                    } else {
                        mainMenu();
                    }
                }
                break;
            case 3: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

// User management functions
void saveUsersToFile() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%s %s %s %s %d %d\n", users[i].username, users[i].password,
                users[i].email, users[i].phone, users[i].frequentRouteCount, users[i].isAdmin);
        for (int j = 0; j < users[i].frequentRouteCount; j++) {
            fprintf(file, "%s\n", users[i].frequentRoutes[j]);
        }
    }
    fclose(file);
}

void loadUsersFromFile() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) return;
    while (fscanf(file, "%s %s %s %s %d %d", users[user_count].username, users[user_count].password,
                  users[user_count].email, users[user_count].phone, &users[user_count].frequentRouteCount,
                  &users[user_count].isAdmin) != EOF) {
        for (int j = 0; j < users[user_count].frequentRouteCount; j++) {
            fscanf(file, "%s", users[user_count].frequentRoutes[j]);
        }
        user_count++;
    }
    fclose(file);
}

void registerUser() {
    if (user_count >= MAX_USERS) {
        printf("User limit reached! Cannot register more users.\n");
        return;
    }
    printf("Enter username: ");
    scanf("%s", users[user_count].username);
    printf("Enter password: ");
    scanf("%s", users[user_count].password);
    printf("Enter email: ");
    scanf("%s", users[user_count].email);
    printf("Enter phone number: ");
    scanf("%s", users[user_count].phone);
    printf("Is this user an admin? (1 for Yes, 0 for No): ");
    scanf("%d", &users[user_count].isAdmin);
    users[user_count].frequentRouteCount = 0;
    user_count++;
    saveUsersToFile();
    printf("Registration successful!\n");
}

int loginUser() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful!\n");
            strcpy(current_user, username);
            current_user_is_admin = users[i].isAdmin;
            return 1;
        }
    }
    printf("Invalid username or password!\n");
    return 0;
}

// Profile management functions
void viewProfile() {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, current_user) == 0) {
            printf("\nUser Profile:\n");
            printf("Username: %s\n", current_user);
            printf("Email: %s\n", users[i].email);
            printf("Phone: %s\n", users[i].phone);
            printf("Frequent Routes:\n");
            if (users[i].frequentRouteCount == 0) {
                printf("- None\n");
            } else {
                for (int j = 0; j < users[i].frequentRouteCount; j++) {
                    printf("- %s\n", users[i].frequentRoutes[j]);
                }
            }
            break;
        }
    }
    displayTickets();
}

void updateProfile() {
    char newPassword[50], newEmail[50], newPhone[15];
    printf("Enter new password (or press Enter to skip): ");
    scanf("%s", newPassword);
    printf("Enter new email (or press Enter to skip): ");
    scanf("%s", newEmail);
    printf("Enter new phone number (or press Enter to skip): ");
    scanf("%s", newPhone);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, current_user) == 0) {
            if (strlen(newPassword) > 0) strcpy(users[i].password, newPassword);
            if (strlen(newEmail) > 0) strcpy(users[i].email, newEmail);
            if (strlen(newPhone) > 0) strcpy(users[i].phone, newPhone);
            saveUsersToFile();
            printf("Profile updated successfully!\n");
            return;
        }
    }
    printf("User not found!\n");
}

void addFrequentRoute() {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, current_user) == 0) {
            if (users[i].frequentRouteCount >= MAX_FREQUENT_ROUTES) {
                printf("Cannot add more frequent routes! Limit is %d.\n", MAX_FREQUENT_ROUTES);
                return;
            }
            printf("Enter route to save (e.g., 'KL to Penang'): ");
            char route[50];
            scanf(" %[^\n]", route);
            strcpy(users[i].frequentRoutes[users[i].frequentRouteCount++], route);
            saveUsersToFile();
            printf("Route saved successfully!\n");
            return;
        }
    }
}

// Main menu for regular users
void mainMenu() {
    char choice;
    while (1) {
        printf(
        "\n===== Bus Reservation System =====\n"
        "1. View Routes & Schedules\n"
        "2. Book a Ticket\n"
        "3. Cancel a Ticket\n"
        "4. View My Tickets\n"
        "5. Exit to Main Menu\n"
        "==================================\n"
        "Enter your choice: ");
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

// Admin menu
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

// Booking and ticket management functions
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
