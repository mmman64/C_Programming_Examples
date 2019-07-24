// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// define node
typedef struct node
{
    int key;
    char value[LENGTH + 1];
    struct node *next;
}
node;

// define bucket
// typedef struct bucket
// {
//     // points to first element in linked list
//     node *head;
//     // points to last element in linked list
//     node *tail;
//     // keeps track of current place in linked list
//     node *cursor;
// }
// bucket;

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H
