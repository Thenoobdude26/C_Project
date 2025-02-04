// Please do not commit to this file, copy and edit on your device.
// and remember to check with everyone before pushing your changes.
// please.
// last edited by: Tatenda
// edited on: 2024-02-14 19:51 


#include <stdlib.h>
#include <stdio.h>

// Function prototypes
void mainMenu();
void bookTicket();
void viewSchedule();
void cancelTicket();
void start();
void login();
void reg();
void AdminMenu();
void busmanagment();
void usagemonitoring();
void genaratereport();


int main() {
    start();  
    return 0;
}

// Function to display the Startiing menu
void start() {
    char choice;
            while (1)
            {
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
"1. Login                                          \n"
"2. Register                                       \n"
"3. Exit                                           \n"
"================================================\n");

        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                login();
                break;
            case '2':
                reg();
                break;
            case '3':
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
            }
}

// Function to display the Main Menu
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
"1. Book a Ticket                                  \n"
"2. View Schedule                                  \n"
"3. Cancel a Ticket                                \n"
"4. Exit                                           \n"
"================================================\n");

        printf("Enter your choice: ");
        scanf(" %c", &choice);  

        switch (choice) {
            case '1':
                bookTicket();
                break;
            case '2':
                viewSchedule();
                break;
            case '3':
                cancelTicket();
                break;
            case '4':
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to handle ticket booking
void bookTicket() {
    printf("\n--- Booking a Ticket ---\n");
    printf("Feature not implemented yet.\n\n");
}

// Function to handle schedule viewing
void viewSchedule() {
    printf("\n--- Viewing Schedule ---\n");
    printf("Feature not implemented yet.\n\n");
}

// Function to handle ticket cancellation
void cancelTicket() {
    printf("\n--- Canceling a Ticket ---\n");
    printf("Feature not implemented yet.\n\n");
}

void login() {
    printf("\n--- Login Page ---\n");
    printf("Feature not implemented yet.\n\n");
}

void reg() {
    printf("\n--- Welcome to the registration page ---\n");
    printf("Feature not implemented yet.\n\n");
}


// Function to display the Admin Menu
void AdminMenu() {
    char choice;
            while (1)
            {
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
"     Welcome to the Admin System menu     !       \n"
"==================================================\n"
"1. Bus Management.                                \n"
"2. Usage monitorting.                             \n"
"3. Generate report.                               \n"
"4. Exit                                           \n"
"================================================\n");

        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                printf("Feature not implemented yet.\n\n");
                break;
            case '2':
                printf("Feature not implemented yet.\n\n");
                break;
            case '3':
                printf("Feature not implemented yet.\n\n");
            case '4':
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
            }
}