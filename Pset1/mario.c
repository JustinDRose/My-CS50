#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do {
        printf("How High?\n");
        h = get_int();
        if (h < 0 || h > 23)
        {printf("Whoops! Positive integers less than 24 please!\n");
    }
    }
    while (h < 0 || h > 23); 
   
    for (int i = 0; i < h; i++)
    {
        for (int s = 1; s < h - i; s++)
        {
            printf(" ");
            
            }
        for (int p = 0; p < 2 + i; p++)
        {
            printf("#");
        }
        printf("\n");
    

}
}
