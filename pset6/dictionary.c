/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

/*for testing
void print_hash();*/

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    //make local copy of word
    char string[strlen(word)+1];
    strcpy(string,word);
    
    // convert word into all lowercase
    for(int i=0; i<strlen(string) ; i++)
    {
        if(isupper(string[i]))
            string[i] = tolower(string[i]);
    }
    
    int hash_val;
    //calculate hash value for word
    hash_val = hash(string);
    
    node* new_node; 
    new_node = ht.arr[hash_val];
    
    //compare with each value of each node in hash table at that bucket
    while(new_node != NULL)
    {
       if(strcmp(string, new_node -> word) == 0)
            return true;
            
       new_node = new_node -> next;
             
    }
    
    free(new_node);
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Implementing load
    
    FILE* fp = fopen(dictionary, "r");
    unsigned int hash_val;
    
    if(fp == NULL)
        return false;
    
    char str[ LENGTH+1 ];
    
    ht.elements = 0;
    
    while(fgets(str, LENGTH+1 , fp))
    {
    
        //fgets reads \n, so replacing it with \0
        str[strlen(str)-1] = '\0';
        
        hash_val = hash(str);  //calculate hash value for read word
       
       // printf("word %s - hash_val %d\n",str,hash_val);
       
        //create new node for it
        node* new_node = malloc(sizeof(node));  
        strcpy(new_node -> word, str); 
        new_node -> next = NULL;  
        
        
        //add to hash table
        if( ht.arr[hash_val] == NULL)
        {
            ht.arr[hash_val] = new_node;
            ht.elements++;
        }
        else
        {
            new_node -> next = ht.arr[hash_val];
            ht.arr[hash_val] = new_node;
            ht.elements++;
        }
    }
    
    //print_hash();
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // 
    return ht.elements;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // unloading
    
    node* cur;
    node* temp; 
    
    for(int i=0; i < HASH_TABLE_SIZE ; i++)
    {
        if(ht.arr[i] != NULL)
        {
            cur = ht.arr[i];
            do
            {   
                temp = cur;
                cur = cur -> next;
                free(temp);
                
            }while(cur != NULL); 
        }
    }
    
  
    return true;
}


/**
*  hash function, takes string key & returns hash value
*/
unsigned int hash(char key[])
{
    unsigned long hash_value= 5381;
    unsigned int c=0, hash;
    
    for(int i=0; key[i] != '\0' ; i++)
    {
        c = key[i];
        //djb2 hash function /* seed*33 + char */
        hash_value = ((hash_value << 5) + hash_value) + tolower(c);
    }  
    
    //table size from 0 to max table size
    hash = hash_value % HASH_TABLE_SIZE;
 
    return hash;  
}

/*
* for testing
*/
/*void print_hash()
{
  node* new_node = malloc(sizeof(node));
    for(int i=1300; i < HASH_TABLE_SIZE ; i++)
    {
        
        if(ht.arr[i] != NULL)
        {
            new_node = ht.arr[i];
            printf("\n%d th bucket\n",i);
            do
            {
                printf(" %s ", new_node -> word);
                new_node = new_node -> next;
                
            }while(new_node != NULL);
                    
        }
       
    }
    
    free(new_node);
    
}*/
