/*******************************************************
This a cs50 problem set 2 assignment program for Caesar 
cipher text.

Author : Amit Paropkari
Date : 21-Feb-2014

It takes key and plain text, and rotates alphabets in 
plain text by keyth position to right to encrypt it. 
*******************************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>



int main(int argc,string argv[])
{
    int k,digit_flag=0;
    string plain_text;
    

    //reading key a argument to program using argc & argv
    if (argc == 2)
    {
       //to check every char of argv[1]
        for(int i=0, n=strlen(argv[1]); i<n; i++)
        {
        //to check if char is digit
        if(isdigit(argv[1][i]))
            digit_flag=1;
        else
         {
           printf("This program needs key - k as an single integer value\n");
           digit_flag=0;
           return 1;
         }
        }
        
        if(digit_flag==1)
        k=atoi(argv[1]);
    }
    else
    {
        printf("This program needs key - k as an single integer value\n");
        return 1;
    }
    
    
   // printf("Enter plain text : ");
    plain_text=GetString();
    
    string ciphered_text = malloc((strlen(plain_text))*sizeof(char));
    
    //Iterate thru each char in plain_text to perform encryption
    for(int i=0,n=strlen(plain_text); i<n ; i++)
    {
        //check if char is alphabet
        if(isalpha(plain_text[i]))
       {
        //if its upper case, rotate by k & store in ciphered text
        if(isupper(plain_text[i]))
        { 
          ciphered_text[i]=(char) (((plain_text[i]-'A'+k)%26)+'A');
         
        }
        //else if lower case, rotate by k & store in ciphered text
        else if(islower(plain_text[i]))
        {
           ciphered_text[i]=(char) (((plain_text[i]-'a'+k)%26)+'a');
          
        }
       
       }
       
        //else if store char as it is
        else
        {
            ciphered_text[i]=plain_text[i];
        }
       
    }
    
    
    printf("%s\n",ciphered_text);
    free(ciphered_text);
        
    return 0;
}
