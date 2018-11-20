#include <cs50.h>
#include <stdio.h> 

int main(void)
{
    printf("How long was your shower (in minutes)? ");
    int t = get_int();
    int b = t * 1.5 * 128 / 16;
    printf("Minutes: %i\nBottles: %i\n", t, b);

    
}
