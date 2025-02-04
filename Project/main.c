#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

// Function prototypes
void mainMenu();
void bookTicket();
void viewSchedule();
void cancelTicket();
void* updateClock(void* arg);

int main() {
    pthread_t clockThread;
    pthread_create(&clockThread, NULL, updateClock, NULL);
    mainMenu();  
    pthread_cancel(clockThread);
    pthread_join(clockThread, NULL);
    return 0;
}

// Function to update the clock
void* updateClock(void* arg) {
    while (1) {
        time_t now;
        time(&now);
        struct tm* local = localtime(&now);
        printf("\rCurrent Time: %02d:%02d:%02d", local->tm_hour, local->tm_min, local->tm_sec);
        fflush(stdout);
        sleep(1);
    }
    return NULL;
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

        printf("\033[K");  // Clear the current line
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
