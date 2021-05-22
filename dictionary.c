// Implementation of a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <strings.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 30; // Max 27 buckets

// Hash table
node *table[N];

// Counting of total number of words
int nWords = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Taking the index in hash table
    int i = hash(word);

    node *list = table[i];
    if (list == NULL)
    {
        return false;
    }
    else
    {
        while (list != NULL)
        {
            if (strcasecmp(list->word, word) == 0)
            {
                return true;
            }
            list = list->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Testing only 26 buckets
    // First letter of a word
    char letter = tolower(word[0]);
    int value = 0;

    switch (letter)
    {
        case 'a':
            value = 0;
            break;
        case 'b':
            value = 1;
            break;
        case 'c':
            value = 2;
            break;
        case 'd':
            value = 3;
            break;
        case 'e':
            value = 4;
            break;
        case 'f':
            value = 5;
            break;
        case 'g':
            value = 6;
            break;
        case 'h':
            value = 7;
            break;
        case 'i':
            value = 8;
            break;
        case 'j':
            value = 9;
            break;
        case 'k':
            value = 10;
            break;
        case 'l':
            value = 11;
            break;
        case 'm':
            value = 12;
            break;
        case 'n':
            value = 13;
            break;
        case 'o':
            value = 14;
            break;
        case 'p':
            value = 15;
            break;
        case 'q':
            value = 16;
            break;
        case 'r':
            value = 17;
            break;
        case 's':
            value = 18;
            break;
        case 't':
            value = 19;
            break;
        case 'u':
            value = 20;
            break;
        case 'v':
            value = 21;
            break;
        case 'w':
            value = 22;
            break;
        case 'x':
            value = 23;
            break;
        case 'y':
            value = 24;
            break;
        case 'z':
            value = 25;
            break;
        default :
            value = 26;
            break;
    }
    return value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Steps:
    // 1. Open directory file
    // 2. Read strings from file one at a time
    // 3. Create a new node for each word
    // 4. Hash word to obtain a hash value
    // 5. Insert node into hash table at that location

    // Step 1
    FILE *fileDictionary = fopen(dictionary, "r");
    // Basic validation
    if (fileDictionary == NULL)
    {
        return false;
    }

    // Step 2
    char words[100];
    while (true)
    {
        if (fscanf(fileDictionary, "%s", words) == EOF)
        {
            // I need to stop the loop at end of file
            break;
        }

        // Step 3
        node *newNode = malloc(sizeof(node));
        //Basic validation
        if (newNode == NULL)
        {
            return false;
        }
        strcpy(newNode->word, words);
        newNode->next = NULL;

        // Step 4
        int i = hash(words);
        // Validation
        if (table[i] == NULL)
        {
            table[i] = newNode;
        }
        else
        {
            newNode->next = table[i];
            table[i] = newNode;
        }
        nWords += 1;

    }
    fclose(fileDictionary);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return nWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = cursor;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
