#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void mainMenu();
void bookTicket();
void viewSchedule();
void cancelTicket();

int main() {
    mainMenu();  
    return 0;
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
        scanf(" %c", &choice);  // Space before %c to remove whitespace

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