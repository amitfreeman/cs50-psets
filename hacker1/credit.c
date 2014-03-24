#include <stdio.h>
#include <cs50.h>


int main(void)
{

int count=0,i;
long long card_number,n;

printf("Number : ");         // Get credit card number from user
card_number=GetLongLong();

//calculate number of digits
n=card_number;
while(n>0)
{
    n=n/10;
    count++;
}


//if its a 13 digit number check if number's first digit is 4,then do checksum
if(count==13)
{
    int a[13],sum_of_odd=0,sum_of_even=0;
   for(n=card_number,i=0;n>0;i++)
   {
      a[i]=n%10;   //store all the digits in an array
      n/=10;
   }
   //do checksum
   if(a[12]==4)
   {
        //loop to calculate sum of digits which will be multiplied by 2 first starting second last digit
        for(i=11;i>0;)
        {
            if((a[i]*2)/10 > 0)
                sum_of_odd+=(1+((a[i]*2)%10));
            else
                sum_of_odd+=(a[i]*2);  
            i-=2;      
        }
        
        //loop to calculate sum of even digits
        for(i=12;i>=0;)
        {
           sum_of_even+=a[i];
           i-=2;
        }
        
 
      if((sum_of_odd+sum_of_even)%10 == 0)  //calculate final sum n check if its divisible by 10
      printf("VISA\n");
      else
      printf("INVALID\n");
   }
   
   else
   printf("INVALID\n");
}

//if its a 15 digit number check if number starts with 34 or 37, then do checksum
else if(count==15)
{
    int a[15],sum_of_odd=0,sum_of_even=0;
    for(n=card_number,i=0;n>0;i++)
   {
      a[i]=n%10;   //store all the digits in array
      n/=10;
   }
   
   ////do checksum
   if(a[14]==3)
   {
    if(a[13]==4 || a[13]==7)
    {
        for(i=13;i>0;)
        {
            if((a[i]*2)/10 > 0)
                sum_of_odd+=(1+((a[i]*2)%10));
            else
                sum_of_odd+=(a[i]*2);  
            i-=2;      
        }
        
        //loop to calculate sum of even digits
        for(i=14;i>=0;)
        {
           sum_of_even+=a[i];
           i-=2;
        }
        
 
      if((sum_of_odd+sum_of_even)%10 == 0)  //calculate final sum n check if its divisible by 10
      printf("AMEX\n");
    }
   } 
   else
   printf("INVALID\n");
}


//if its a 16 digit number check if number starts with 4 or 51,52,53,54 or 55, then do checksum
else if(count == 16)
{
    int a[16],sum_of_odd=0,sum_of_even=0;
    for(n=card_number,i=0;n>0;i++)
   {
      a[i]=n%10;   //store all the digits in array
      n/=10;
   }
   
   //do checksum for visa
   if(a[15]==4)
   {
        //loop to calculate sum of digits which will be multiplied by 2 first starting second last digit
        for(i=14;i>0;)
        {
            if((a[i]*2)/10 > 0)
                sum_of_odd+=(1+((a[i]*2)%10));
            else
                sum_of_odd+=(a[i]*2);  
            i-=2;      
        }
        
        //loop to calculate sum of even digits
        for(i=15;i>=0;)
        {
           sum_of_even+=a[i];
           i-=2;
        }
        
// printf("Sum of odd %d \n sum of even %d \n total %d \n",sum_of_odd,sum_of_even,sum_of_odd+sum_of_even);
      if((sum_of_odd+sum_of_even)%10 == 0)  //calculate final sum n check if its divisible by 10
      printf("VISA\n");
      else
      printf("INVALID\n");
   }
   
   //do checksum for Master Card
   else if(a[15] == 5)
   {
     if(a[14]==1 || a[14]==2 || a[14]==3 || a[14]==4 || a[14]==5)
     {
        //loop to calculate sum of digits which will be multiplied by 2 first starting second last digit
        for(i=14;i>0;)
        {
            if((a[i]*2)/10 > 0)
                sum_of_odd+=(1+((a[i]*2)%10));
            else
                sum_of_odd+=(a[i]*2);  
            i-=2;      
        }
        
        //loop to calculate sum of even digits
        for(i=15;i>=0;)
        {
           sum_of_even+=a[i];
           i-=2;
        }
        
 //printf("sum of odd %d \n sum of even %d \n total %d \n",sum_of_odd,sum_of_even,sum_of_odd+sum_of_even);
      if((sum_of_odd+sum_of_even)%10 == 0)  //calculate final sum n check if its divisible by 10
      printf("MASTERCARD\n");
      else
      printf("INVALID\n");
     }
   }
   
   else
   printf("INVALID\n");
}

//last else
else
{
    printf("INVALID\n");
}

return 0;
}
