#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


typedef uint8_t byte;
 

int main(int argc, char* argv[])
{
    
    if (argc != 2)
    {
        fprintf(stderr, "Error, please enter the filename of the file you'd like to recover!\n");
        return 1;
    }
    
    char *card = argv[1];
    FILE *inptr = fopen(card, "r");
    
    if (inptr == NULL)
    {
        fprintf(stderr, "Error, file could not be opened\n");
        return 2;
    }
    
    int count = 0;
    bool found = false;
    char filename [8];
    byte buffer[512];
    FILE *img;
    
    while (fread(buffer, 1, 512, inptr) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (found == false)
            {
                found = true;
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
            
            else
            {
                fclose(img);
                count++;
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
                
            }
        }
        
        else
        {
            if (found == true)
            {
                fwrite(buffer, 1, 512, img);
            }
        }
    }
     if(img)
        {
            fclose(img);
        }
    fclose(inptr);
   
return 0;   
}
