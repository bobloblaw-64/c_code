#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ROT 13

/* Rotate c returns the character ROT positions further along the
   alphabetic character sequence from c, or c if c is not lower-case */
char rotate(char c)
{
    // Check if c is lower-case or not
    if(islower(c))
    {
        /* The ciphered character is ROT positions beyond c,
           allowing for wrap-around */
        return('a' + (c - 'a' + ROT) % 26) ;
    }
    else
    {
        return c;
    }
}

int main(int argcount, char *argvalue[])
{
    /* Exit with an error if the the number of arguments (including
       the name of the executable) is not precisely 2 */
    if(argcount != 2)
    {
        fprintf(stderr, "%s: program expected 1 argument, received %d\n",
                argvalue[0], argcount-1) ;
        exit(EXIT_FAILURE) ;
    }
    else
    {
        // Calculate the length of the first argument
        int length = strlen(argvalue[1]) ;

        // Loop for every character in the text
        for(int i = 0; i < length; i++)
        {
            // Determine and print the ciphered character
            printf("%c %c\n", rotate(argvalue[1][i]), argvalue[1][i]);
        }

        

        // Exit indicating success
        exit(EXIT_SUCCESS) ;
    }

    return 0;
}

/* Compile this program as:
   cc -std=c11 -Wall -Werror -o rotate rotate.c
*/
