# Dictionary Functionality Implementation

## Project Description
This project implements the functionality of a dictionary using a hash table. The program includes functions to load words from a dictionary file into memory, check if a word is in the dictionary, return the size of the dictionary, and unload the dictionary from memory.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Algorithm Explanation](#algorithm-explanation)
- [Code Explanation](#code-explanation)

## Installation
No special installation is required for this project. 

## Usage
To compile and run the project, use the following commands:
```sh
make dictionary
./dictionary
```
You will need to provide a dictionary file to load words from.

## Algorithm Explanation
The program uses a hash table to store words from the dictionary. The main components of the algorithm are as follows:

Load Dictionary:
Open the dictionary file.
Read each word from the file and hash it to determine its index in the hash table.
Insert the word into the hash table at the appropriate index.
Check Word:
Hash the input word to determine its index in the hash table.
Traverse the linked list at that index to see if the word exists in the dictionary.
Dictionary Size:
Traverse the entire hash table to count the number of words.
Unload Dictionary:
Traverse the hash table and free all allocated memory.

## Code Explanation
Including Libraries and Function Prototypes
``` C
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"
```
#include <ctype.h>: Includes functions for character classification and conversion.
#include <stdbool.h>: Includes support for the boolean data type.
#include <stddef.h>: Defines several useful types and macros.
#include <stdio.h>: Includes standard input/output functions.
#include <stdlib.h>: Includes functions for memory allocation and process control.
#include <string.h>: Includes string handling functions.
#include <strings.h>: Includes functions for string operations.
#include "dictionary.h": Includes the dictionary header file for function prototypes and definitions.
Defining Node and Hash Table
```C
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
```
Node Structure: Defines a node structure to store words and a pointer to the next node.
N Constant: Defines the number of buckets in the hash table. In this case, 26 buckets, one for each letter of the alphabet.
Hash Table: Declares a hash table as an array of node pointers with N buckets.
Check Function
``` C
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
```
Hash the Word:
``` C
int hash_index = hash(word);
```
Hashes the input word to get the index in the hash table.
Traverse the Linked List:
``` C
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
```
Traverses the linked list at the hashed index to check if the word exists.
Hash Function
``` C
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
```
Calculate Hash:
``` C
int len = strlen(word);
int number = 0;
for (int i = 0; i < len - 1; i++)
{
    number += toupper(word[i]) + toupper(word[i + 1]) - 'A';
}
number = number % N;
return number;
```
Calculates a hash value for the word by summing the values of its characters and taking the modulus with N.
Load Function
``` C
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
```
Open Dictionary File:
``` C
FILE *file = fopen(dictionary, "r");
if (file == NULL)
{
    printf("Could not open file\n");
    return false;
}
```
Opens the dictionary file for reading.
Read Words from File:
``` C
char word[LENGTH + 1];
while (fscanf(file, "%s", word) != EOF)
{
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
```
Reads each word from the file, hashes it, and inserts it into the hash table.
Size Function
``` C
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
```
Count Words in Dictionary:
``` C
int counter = 0;
for (int i = 0; i < N; i++)
{
    for (node *current_node = table[i]; current_node != NULL; current_node = current_node->next)
    {
        counter++;
    }
}
return counter;
```
Traverses the entire hash table and counts the number of words.
Unload Function
``` C
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
```

Free Memory:
``` C
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
```
Traverses the hash table and frees all allocated memory for the nodes.
