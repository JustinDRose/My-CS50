#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//takes command line argument as key only allowing 2 arguments and alpha only for key
int main (int argc, string argv[])
{
if (argc != 2)
{
	printf("ERROR: one command line argument only please!\n");
	return 1;
}
else
{
	for (int i = 0, n = strlen(argv[1]); i < n; i++)
	{
		if (! isalpha(argv[1][i]))
		{
			printf("ERROR: alphabetic symbols for key only! Try Again.\n");
			return 1;	
		}
	}
}

//declaring variables to be used 
int k = 0;
int j = 0;
int nk = strlen(argv[1]);

//get message and setup print-out
string key = argv[1];

printf("plaintext:  ");

string message = get_string();

printf("ciphertext: ");


//loop through message
for (int i = 0, n = strlen(message); i < n; i++)
{
//wraps key back to beginning if finished 
	if (j >= nk)
	{
	j = 0;
	}
//normalizes key char to 0-25
	if isupper(key[j])
	{
	k = key[j] - 65;
	j++;
	}
		
	else if islower(key[j])     
	{
	k = key[j] - 97;
	j++;
	}

//applies key to message and prints ciphered char accounting for wrap 		
	if isupper(message[i])
	{
	int cypher_char = ((message[i] + k) - 65) % 26 + 65;
	printf("%c", cypher_char);
	}
	
	else if islower(message[i])
	{
	int cypher_char = ((message[i] + k) - 97) % 26 + 97;
	printf("%c", cypher_char);
	}
//j-- was used to account for spaces or non-alphabetical chars essentially holding j's value through the loop until next alphabetical 	
	else 
	{printf("%c", message[i]);
	 j--;
	}

}

printf("\n");
return 0;
}



			
				
