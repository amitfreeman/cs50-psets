/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Author : Amit Paropkari
 * Date : 23-03-2014
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//to manipulate byte
typedef uint8_t BYTE;


int main(int argc, char* argv[])
{
    
    FILE* raw_file = fopen("card.raw", "r");
    
    if(raw_file == NULL)
    {
        printf("File not found\n");
        return 1;
    }
    
    BYTE chunk[512];
    char name[8];
    int num = 0;
    bool image_found = false, first = false;
    FILE* new_file;
    
    // read while 512 bytes at a time is read
    while(fread(chunk, 512 * sizeof(BYTE), 1, raw_file) == 1)
    {
   
        //check if new jpg is found
        if(chunk[0] == 0xff && chunk[1] == 0xd8 && chunk[2] == 0xff && (chunk[3] == 0xe0 || chunk[3] == 0xe1))
        {
            //if its a first image found
            if(!first)
            {
                sprintf(name, "%.3d" , num++);
                strcat(name, ".jpg");
                //create new file
                new_file = fopen(name , "a");
                
                if(new_file == NULL)
                {
                    printf("Can't create file\n");
                    return 10;
                }
                
                first = true;
                image_found = true;
                
                //write to new file
                fwrite(chunk , 512 * sizeof(BYTE) , 1 , new_file);
            }
            // else close already opened file & create new one
            else
            {
                //check & close already opened file
                if(new_file != NULL) 
                    fclose(new_file);
                else
                {
                    printf("File error\n");
                    return 20;
                }    
                
                sprintf(name, "%.3d" , num++);
                strcat(name, ".jpg");
                //create new file
                new_file = fopen(name , "a");
                
                if(new_file == NULL)
                {
                    printf("Can't create file\n");
                    return 10;
                }
                
                image_found = true;
                
                //write to new file
                fwrite(chunk , 512 * sizeof(BYTE) , 1 , new_file);
            }
        
            
        }
        else if(image_found)
        {
            //write to existing file
            fwrite(chunk , 512 * sizeof(BYTE) , 1 , new_file);
        }
    }
    
    if(new_file != NULL)
        fclose(new_file);
        
    fclose(raw_file);
    
    return 0;
}
