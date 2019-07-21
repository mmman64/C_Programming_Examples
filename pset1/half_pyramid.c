#include <stdio.h>
#include <string.h>

/*
    Newline finder found at: https://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1044652485&id=1043284385
*/

/*
    Modified function from:
    https://www.programmingsimplified.com/c/source-code/c-program-convert-string-to-integer-without-using-atoi-function
 */
int toInt(char[]);

int main(void)
{
    // declare height variable
    int height;
    // allocate memory for user input
    char str[10];
    // declare variable for newline search
    char *p;

    // keep prompting user for height until condition satisfied
    do
    {
        printf("Enter pyramid height (0 - 23): ");
        fgets(str, 10, stdin);
        // search for newline and replace with null terminator
        if ((p = strchr(str, '\n')) != NULL)
            *p = '\0';
        height = toInt(str);
    } while (height < 0 || height > 23);

    // pyramid components
    char block = '#';
    char space = ' ';

    // create pyramid
    for (int i = 1; i < height + 1; i++)
    {
        // initialise space count
        int spaceCount = height - i;
        // initialise block count
        int blockCount = i + 1;

        for (int s = spaceCount; s > 0; s--)
        {
            printf("%c", space);
        }
        for (int b = 0; b < blockCount; b++)
        {
            printf("%c", block);
        }
        printf("\n");
    }
} // end

// removed code handling negative integers
int toInt(char a[])
{
    int c, n;
    n = 0;

    for (c = 0; a[c] != '\0'; c++)
    {
        n = n * 10 + a[c] - '0';
    }
    return n;
}
