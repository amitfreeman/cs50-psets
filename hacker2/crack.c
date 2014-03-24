/*******************************************************
This a cs50 problem set 2 hacker edition assignment program 
to crack passwords stored in UNIX file system /etc/passwd
 
Author : Amit Paropkari
Date : 21-Feb-2014
 
*******************************************************/

#define _XOPEN_SOURCE

#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>
#include<unistd.h>

#define MIN_PASSWD_LENGTH 6
#define MAX_PASSWD_LENGTH 8 

int brute_force(string ciphered,string salt);

int dict_search(string ciphered, string salt);

int main(int argc,string argv[])
{
    string encrypted = NULL, salt = NULL;
    
    //check if argument is provided
   if(argc==2)
    {
        
        encrypted = malloc((strlen(argv[1])+1)*sizeof(char));
        salt = malloc(2*sizeof(char));
        strcpy(encrypted,argv[1]);
        //extract the salt, firs two chars of password
        strncpy(salt,argv[1],2);
        printf("e %s, salt %s \n",encrypted,salt);
    }
    else
    {
        printf("Provide encrypted password in quotes to program, [usage : ./crack \"password\"]\n");
        return 100;
    }
    

if(dict_search(encrypted,salt) == 0)
{
    free(encrypted);
    free(salt);
    return 0;
}

if(brute_force(encrypted,salt) == 0)
{
    free(encrypted);
    free(salt);
    return 0;
}


   free(encrypted);
    free(salt);   
printf("could not find password\n");

return 0;	
}



//use dictionary search

int dict_search(string ciphered, string salt)
{
    printf("Searching password using dictionary words... \n");
    
    string file_path = "/usr/share/dict/words";
    
    string read = malloc(50 * sizeof(char));
    string crypted = malloc(50 * sizeof(char));
   
    FILE* p = fopen(file_path,"r");
    
    int n;
    
    if(p == NULL)
    {
        printf("\n file not found \n");
    }
    else
    {
        while(fgets(read,50,p))
        {
           //fgets attaches next line (\n) char at the end of string,
           //so to make it null terminated string
            n = strlen(read);
            if(n > 0 && read[n-1] == '\n')
                read[n-1] = '\0';
            
            //encrypt that word using crypt
            crypted = crypt(read,salt);
            
            if(strcmp(crypted,ciphered) == 0)
            {
                printf("Password found - %s \n",read);
                return 0;
             }
        }
    }
    
    free(read);
    fclose(p);
    
  return 1;  
} 



//use brute force
int brute_force(string ciphered, string salt)
{

printf("Using brute force ... \n");
//possible char set for guessing plain text
string char_set = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789 !@#$%^&*()-_";
//string char_set = "abcdefghijklmnopqurstuvwxyz1234567890";

int set_len = strlen(char_set);
char plain[MAX_PASSWD_LENGTH+1];
int pos[] = {0,0,0,0,0,0,0,0}; 



// start
for(int max_len=MIN_PASSWD_LENGTH; max_len<= MAX_PASSWD_LENGTH; max_len++)
   {
          printf("Trying length %d\n", max_len);
           
           bool loop_completed = false;
           
           //initialize word
           for(int ch=0; ch<max_len ; ch++)
                plain[ch] =  char_set[0];
                
            plain[max_len] = '\0';
          
          
          while(!loop_completed)
          {
            //encrypt word and compare
            if(strcmp(crypt(plain,salt),ciphered) == 0)
            {
                printf("password found - %s \n", plain);
                return 0;
            }
            
             bool shift = true;
            
            for (int ch = 0; ch < max_len; ch++)
            {
                // If shift - change character
                if (shift)
                {
                    // If all character are done
                    if (pos[ch] == set_len - 1)
                    {
                        // If last symbol - loop is over
                        if (ch == max_len)
                            loop_completed = true;
                        // Change to first symbol again
                        else
                        {
                            pos[ch] = 0;
                            plain[ch] = char_set[pos[ch]];
                        }
                    }
                    else
                    {
                        plain[ch] = char_set[++pos[ch]];
                        shift = false;
                    }
                }
          }
                
            
   }



 }
 
 return 1;
 
}

