/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
//#define HASH_TABLE_SIZE 4096
#define HASH_TABLE_SIZE 51200  //for minimum number of nodes in bucket 

/**
*   Declaration of node
*/
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
} node;


/**
*    Declaration of hash table of HASH_TABLE_SIZE
*/
typedef struct 
{
    node* arr[HASH_TABLE_SIZE];
    int elements;
    
}hash_table;

hash_table ht;

/**
*   Declaration of hash function, takes key & return hash value
*/
unsigned int hash(char* key);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H
