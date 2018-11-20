#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main (int argc, string argv[])
{
    //make sure only 1 argument for key
    if (argc == 2)
    {
        //change string key to int key
        int key = atoi(argv[1]);

        //get plaintext string
        printf("plaintext:  ");
        string message = get_string();

        //set up cipher text line
        printf("ciphertext: ");

        //loop through message
        for (int i = 0, n = strlen(message); i < n; i++)
        {
            int ci = message[i];

            int wrapcheck = ci + key;

          //Upper: if it doesnt wrap print it with key change
            if (ci > 64 && ci < 91 && wrapcheck < 91)
            {
                ci = wrapcheck;
                printf("%c", ci);
            }

          //Upper: reduce total wrap by alphabet total and add...if still over 'Z' wrap around to beginning
            else if (ci > 64 && ci < 91 && wrapcheck > 90)
            {
                int dif = key % 26;
                ci = ci + dif;
                if (ci > 122)
                {
                    ci = ci - 26;
                    printf("%c", ci);
                }
                else printf("%c", ci);
            }

          //Lower: if it doesnt wrap print it with key change
            else if (ci > 96 && ci < 123 && wrapcheck < 123)
            {
                ci = wrapcheck;
                printf("%c", ci);
            }

          //Lower: reduce total wrap by alphabet total and add... if still over 'z' wrap around to beginning
            else if (ci > 96 && ci < 123 && wrapcheck > 122)
            {
                int dif = key % 26;
                ci = ci + dif;
                 if (ci > 122)
                {
                    ci = ci - 26;
                    printf("%c", ci);
                }
                else printf("%c", ci);
            }

          //Allow for random characters without changing them
            else
            {
                printf("%c", ci);
            }
        }

    }

    //arguments that arent 2... on second thought I cound have just done a if != 2 for the error.
    else
    {
        printf("ERROR: one command line argument only please!\n");
        return 1;
    }
    printf("\n");
    return 0;
}

//I realized when I was done that this could have been done much more elegantly by normalizing to 26 in the beginning
