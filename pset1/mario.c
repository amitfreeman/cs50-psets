#include<stdio.h>
#include<cs50.h>

void make_stairs(int n);

int main(void)
{
  
       printf("Enter height (0-23) :  \n");
       int i=GetInt();   //Read from user
       
    while(true)
    {
       if(i>=0 && i<24)  //check if number is between 0 n 23
       {
         make_stairs(i);  //call function
         break;           // get out of loop
         }
       else
      {
         printf("Height: ");  //if number is not in the range
         i=GetInt();
       }
    }
    
 return 0;
}

void make_stairs(int n)
{
    int i,j;
    
    for(i=1;i<=n;i++)    //for n number of lines
    {
        for(j=n-i;j>0;j--)    //for printing n-i spaces
        printf(" ");
        
        for(j=1;j<=i;j++)      //for printing actual block
        printf("#");
        
        printf("#\n");         //next line
    }
}
