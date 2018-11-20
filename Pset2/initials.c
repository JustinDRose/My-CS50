#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

#define SPACE ' '

int main (void)
{
    //Get string name
    string name = get_string();

    //Null Check
    if (name != NULL)
    {
        //Print first char, will always be first initial given parameters
        printf("%c", toupper(name[0]));

        //Iterate through - No n = strlen as \n is tricky until end of string
        for (int i = 0; ; i++)
     {
         //If loop sees space, print char after space as new initial; Once it reaches end of string print new line
            if (name[i] == SPACE)
        {
                printf("%c", toupper(name[i+1]));
        }
            else if (name[i] == '\0')
            {
                printf("\n");
                return 0;
            }

     }
    }



}
