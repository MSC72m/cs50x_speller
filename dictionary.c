// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_index = hash(word);
    node *first_node = table[hash_index];
    while (first_node != NULL)
    {
        if (strcasecmp(first_node->word, word) == 0)
        {
            return true;
        }
        first_node = first_node->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int len = strlen(word);
    int number = 0;
    for (int i = 0; i < len - 1; i++)
    {
        number += toupper(word[i]) + toupper(word[i + 1]) - 'A';
    }
    number = number % N;
    return number;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open file\n");
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // load the word into your data structure
        int index_table = hash(word);
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Could not open file\n");
            return false;
        }
        strcpy(new_node->word, word);
        new_node->next = NULL;
        if (table[index_table] == NULL)
        {
            table[index_table] = new_node;
        }
        else
        {
            new_node->next = table[index_table];
            table[index_table] = new_node;
        }
    }
    fclose(file);
    return true;
}
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int counter = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *current_node = table[i]; current_node != NULL; current_node = current_node->next)
        {
            counter++;
        }
    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *temp;
    for (int i = 0; i < N; i++)
    {
        for (node *current_node = table[i]; current_node != NULL; current_node = temp)
        {
            temp = current_node->next;
            free(current_node);
        }
    }
    return true;
}
