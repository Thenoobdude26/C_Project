#include <stdio.h>

int main() {
    // int count_star;
    // int N;

    // count_star = 0;

    // printf ("Enter the number of stars: \n");
    // scanf ("%d", &N);

    // while (count_star<  N){
    //     printf ("*");
    //     count_star++;
// }
    char answer;
    char response;

    printf ("Are you a good boy~? (y/n) \n");
    scanf ("%c", &answer);

    if (answer == 'Y' || answer == 'y'){
        printf ("That's right you are~ Good boy~\n");
        printf (
    "⣿⣿⡇⢩⠘⣴⣿⣥⣤⢦⢁⠄⠉⡄⡇⠛⠛⠛⢛⣭⣾⣿⣿⡏\n"
    "⣿⣿⣿⡇⠹⢇⡹⣿⣿⣛⣓⣿⡿⠞⠑⣱⠄⢀⣴⣿⣿⣿⣿⡟\n"
    "⣿⣿⣿⣧⣸⡄⣿⣪⡻⣿⠿⠋⠄⠄⣀⣀⢡⣿⣿⣿⣿⡿⠋\n"
    "⠘⣿⣿⣿⣿⣷⣭⣓⡽⡆⡄⢀⣤⣾⣿⣿⣿⣿⣿⡿⠋\n"
    "⠄⢨⡻⡇⣿⢿⣿⣿⣭⡶⣿⣿⣿⣜⢿⡇⡿⠟⠉\n"
    "⠄⠸⣷⡅⣫⣾⣿⣿⣿⣷⣙⢿⣿⣿⣷⣦⣚⡀\n"
    "⠄⠄⢉⣾⡟⠙⠶⠖⠈⢻⣿⣷⣅⢻⣿⣿⣿⣿⣿⣶⣶⡆⠄⣤⡀\n"
    "⠄⢠⣿⣿⣧⣀⣀⣀⣀⣼⣿⣿⣿⡎⢿⣿⣿⣿⣿⣿⣿⣇⠄⠈⠁\n"
    "⠄⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢇⣎⢿⣿⣿⣿⣿⣿⣿⣿⣶⣶\n"
    "⠄⠄⠻⢿⣿⣿⣿⣿⣿⣿⣿⢟⣫⣾⣿⣷⡹⣿⣿⣿⣿⣿⣿⣿⡟\n"
    "⠄⠄⠄⠄⢮⣭⣍⡭⣭⡵⣾⣿⣿⣿⡎⣿⣿⣌⠻⠿⠿⠿⠟⠋\n"
    "⠄⠄⠄⠄⠈⠻⣿⣿⣿⣿⣹⣿⣿⣿⡇⣿⣿⡿\n"
    "⠄⠄⣀⣴⣾⣶⡞⣿⣿⣿⣿⣿⣿⣿⣾⣿⡿\n"
        );
    } else {
        printf ("naughty naughty boy~\n");
    }
    return 0;
}