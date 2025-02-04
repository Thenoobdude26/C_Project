#include <stdio.h>

int main() {
    int count_star;
    int N;

    count_star = 0;

    printf ("Enter the number of stars: \n");
    scanf ("%d", &N);

    while (count_star<  N){
        printf ("*");
        count_star++;
    }
    
    return 0;
}