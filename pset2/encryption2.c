#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET 26
// use key, keylength, user string, and length of user string to apply encryption
string encryptor(string key, int keyLength, string input, int inputLength);

// allow user to pass command line arguments
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        // print error displaying correct usage
        printf("Usage: ./vigenere k\n");
        // end program
        return 1;
    }
    // keyword for encoding message
    string keyCode = argv[1];
    // get length of keycode for alphabet index assignment
    int codeLength = strlen(keyCode);

    // check that suitable keycode supplied
    for (int i = 0; i < codeLength; i++)
    {
        // reject if not alphabetical
        if (!isalpha(keyCode[i]))
        {
            // print error displaying correct usage
            printf("Usage: ./vigenere k\n");
            // end program
            return 1;
        }
    }
    // get plaintext from user
    string message = get_string("plaintext: ");
    // get length of input
    int textLength = strlen(message);
    // test validity of input
    if (textLength < 1)
    {
        // print error displaying correct usage
        printf("Usage: ./vigenere k\n");
        // end program
        return 1;
    }
    string cipher = encryptor(keyCode, codeLength, message, textLength);
    printf("ciphertext: %s\n", cipher);

    return 0;
} // end main

// encrypt user input according to key
string encryptor(string key, int keyLength, string input, int inputLength)
{
    // loop through input
    for (int i = 0, j = 0; i < inputLength; i++)
    {
        // just print character if not alphabetical and go to next letter
        if (!isalpha(input[i]))
        {
            input[i] = input[i];
            continue;
        }

        // sort key into groups by index
        int group = j % keyLength;
        // offset the ascii code by upper or lower
        int inputOffset = isupper(input[i]) ? 65 : 97;
        // get the position in alphabet by applying the offset
        // e.g. "H" -> 72 - 65 = 7 (zero index based)
        int alphabetIndex = input[i] - inputOffset;
        // offset the ascii code by upper or lower
        int keyOffset = isupper(key[group]) ? 65 : 97;
        // gives alphabet index of appropiate keycode
        // e.g. group = 0 -> key[0] = b -> index 1 in alphabet
        int keyIndex = key[group] - keyOffset;
        // gives alphabet index after applying key
        int newAlphabetIndex = (alphabetIndex + keyIndex) % 26;
        // get back to ascii for actual char representation
        input[i] = newAlphabetIndex + inputOffset;

        j++;
    } // end for

    return input;
} // end encryptor