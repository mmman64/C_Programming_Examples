#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

#define HASHTABLE_SIZE 5419

// declare dictionary file variable
FILE *dictionary_file;
// initialise dictionary
node **hashtable;
// declare variable for number of words in dictionary
int hash_table_size;
// get hash used to assign word to bucket
int hash(char *word);
// assign word to bucket
void assign_to_bucket(char *word, int key);
// insert word in dictionary / node in linked list
void insert_node(node **head, char *word);
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // initialise variable to hold word for string manipulation
    char str_word[LENGTH + 1];
    // include null charcter
    str_word[LENGTH] = '\0';
    // copy word value for string manipulation
    strcpy(str_word, word);
    // get length of string
    int num = strlen(str_word);

    // turn upper case characters to lower case
    while (num > 0)
    {
        if (isupper(str_word[num - 1]))
        {
            str_word[num - 1] = tolower(str_word[num - 1]);
        }
        num--;
    }
    // get hash value that correlates to hashtable bucket
    int hash_value = hash(str_word) % HASHTABLE_SIZE;
    // point to initial pointer
    node *current = hashtable[hash_value];

    // keep checking until end of list
    while (current != NULL)
    {
        // if match is found assume word correctly spelt
        if (strcasecmp(str_word, current->value) == 0)
        {
            return true;
        }
        // move cursor to next node
        current = current->next;
    }
    // word not found, checked word assumed to be misspelt
    return false;
}
// loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary file
    dictionary_file = fopen(dictionary, "r");
    // end if unsuccessful
    if (dictionary_file == NULL)
    {
        return false;
    }
    // allocate memory for pointers
    hashtable = calloc(HASHTABLE_SIZE, sizeof(node *));
    // initialise number of elements in hash table to 0
    hash_table_size = 0;
    // allocate memory to word, including null character
    char word[LENGTH + 1];
    // include null charcter
    word[LENGTH] = '\0';

    // scan dictionary word by word
    while (fscanf(dictionary_file, "%s", word) != EOF)
    {
        // give word a hash value
        int key = hash(word);
        // assign word to bucket based on hash value
        assign_to_bucket(word, key);
        // increment size of hash table
        hash_table_size++;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return hash_table_size > 0 ? hash_table_size : 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // declare node pointer variable
    node *head;
    // free each node in the linked list
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        head = hashtable[i];
        node *current = head;

        while (current != NULL)
        {
            node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    // free memory allocated to hashtable
    free(hashtable);
    // close the dictionary file
    fclose(dictionary_file);
    // return true if successful else false
    return true;
}

/*
* Hash function taken from:
* https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn/
* Some naming changes made.
*/
int hash(char *word)
{
    unsigned int hash_num = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash_num = (hash_num << 2) ^ word[i];
    }
    return hash_num % HASHTABLE_SIZE;
}

void assign_to_bucket(char *word, int key)
{
    // if bucket does not yet exist
    if (hashtable[key] == NULL)
    {
        // initialise head pointer
        node *head = NULL;
        // insert word
        insert_node(&head, word);
        // head points to first node in linked list
        hashtable[key] = head;
    }
    else
    {
        // bucket exists
        node *head = hashtable[key];
        // insert word
        insert_node(&head, word);
        // head points to first node in linked list
        hashtable[key] = head;
    }
}

void insert_node(node **head, char *word)
{
    // malloc a node for each new word
    node *new_node = malloc(sizeof(node));
    // check memory allocation successful
    if (new_node == NULL)
    {
        return;
    }
    // copy word to node
    strcpy(new_node->value, word);
    // if head is not pointing to anything, point head to new_node
    if (*head == NULL)
    {
        // make head point to new_node
        *head = new_node;
        // make new_node point to NULL
        new_node->next = NULL;
    }
    else
    {
        // make new_node point to what head is already pointing to
        new_node->next = *head;
        // make head point to new node
        *head = new_node;
    }
}
