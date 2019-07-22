#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// alphabet size
#define ALPHABET 26

/*
    Modified function from:
    https://www.programmingsimplified.com/c/source-code/c-program-convert-string-to-integer-without-using-atoi-function
 */
int toInt(char[]);

string encryptor(int key, string input);

// allow user to pass params on start
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar k");
        return 1;
    }

    // get passed param as int
    int k = toInt(argv[1]);
    // get plaintext from user
    string p = get_string("plaintext: ");
    // pass key and phrase to encrypt to encryptor
    string cipher = encryptor(k, p);
    // output result
    printf("ciphertext: %s\n", cipher);

    return 0;
}

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

// use key and user string to apply encryption
string encryptor(int key, string input)
{
    // loop through the plaintext by character
    for (int i = 0; i < strlen(input); i++)
    {
        // just print character if not alphabetical and go to next letter
        if (!isalpha(input[i]))
        {
            input[i] = input[i];
            continue;
        }
        // offset the ascii code by upper or lower
        int offset = isupper(input[i]) ? 65 : 97;
        // get the position in alphabet by applying the offset
        // e.g. "H" -> 72 - 65 = 7 (zero index based)
        int alphabetIndex = input[i] - offset;
        // gives alphabet index after applying the key
        int newAlphabetIndex = (alphabetIndex + key) % 26;
        // get back to ascii for actual char representation
        char newChar = newAlphabetIndex + offset;

        // replacing letters in original string to save memory
        input[i] = newChar;
    }
    return input;
}
