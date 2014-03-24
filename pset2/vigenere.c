/*******************************************************
This a cs50 problem set 2 assignment program for vigenere 
cipher text.

Author : Amit Paropkari
Date : 21-Feb-2014

It takes aplhabetical word key and plain text, and encrypts 
plain text using mixture of word length, value & mix of caesar
cypher. 
*******************************************************/

#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>

int main(int argc,string argv[])
{
   
    int alpha_flag=0;
    string key=NULL,ciphered_text=NULL;
    
    //reading key a argument to program using argc & argv
    if (argc == 2)
    {
       //to check every char of argv[1]
        for(int i=0, n=strlen(argv[1]); i<n; i++)
        {
        //to check if char is alphabet
        if(isalpha(argv[1][i]))
            alpha_flag=1;
        else
         {
           printf("This program needs key - k as one alphabetical word\n");
           alpha_flag=0;
           return 1;
         }
        }
        
        if(alpha_flag==1)
        {
            
            //allocating memory for key string same size of argv[1]
            key=malloc(strlen(argv[1])*sizeof(char));
            
            //converting argv[1] to all lower case letter word and storing into
            //key for easy calculation futhur
            for(int i=0,n=strlen(argv[1]);  i<n ; i++)
            {
                if(isupper(argv[1][i]))
                key[i]=(char) (tolower(argv[1][i]));
                else
                key[i]=(char) (argv[1][i]);
            }
            
            //strcat(key,'\0');
            //printf("%s\n",key);
        }
        
    }
    else
    {
        printf("This program needs key - k as one alphabetical word\n");
        return 1;
    }
    
    string plain_text=GetString();              //getting plain text from user
    int npt=strlen(plain_text), nk=strlen(key), k=0;    //length of plain text & key & kth position
    
    
    ciphered_text = malloc((strlen(plain_text))*sizeof(char)); //make memory for ciphered text
    
    for(int i=0,j=0; i<npt ;i++)
    {
        
        
        if(isalpha(plain_text[i]))
        {
        
            if(j == nk)   //if last char of key is reached, start from initial one again
            {
             j=0;
             k=key[j]-'a';    //calculate position of char relative to a, hence shift digit
              j++;            
            }
            else
             {
               k=key[j]-'a';     //calculate position of char relative to a, hence shift digit
               j++;
             }
        
        
        //same logic as Caesar cypher
            if(isupper(plain_text[i]))
            {
                 ciphered_text[i]=(char) (((plain_text[i]-'A'+k)%26)+'A');
            }
            if(islower(plain_text[i]))
            {
                 ciphered_text[i]=(char) (((plain_text[i]-'a'+k)%26)+'a');
            }
        }
        
        else
        {
            ciphered_text[i]=plain_text[i];
        }
    }

printf("%s\n",ciphered_text);
free(ciphered_text);
free(key);

return 0;
}
