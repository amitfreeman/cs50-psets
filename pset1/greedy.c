#include<stdio.h>
#include<math.h>
#include<cs50.h>

int main()
{
    float change=0;
    printf("O hai! How much change is owed?\n");
    change=GetFloat();            //get change
    
    while(true)
    {
        if(change>=0)    //check if non-negative
        {
            int amount=(int) round(changle*100);   //calculate actual change
            //printf("amount=%d\n",amount);
            
            int count=0,quarter=0,dime=0,nickel=0,penny=0;
            while(amount>0)  //loop to compare with quarter(25),dime(10),nickel(5),pennys(1)
            {
                if(amount>=25)
                {
                    count++;
                    amount=amount-25;
                    quarter++;
                }
                else if(amount>=10)
                {
                    count++;
                    amount=amount-10;
                    dime++;
                }
                else if(amount>=5)
                {
                    count++;
                    amount=amount-5;
                    nickel++;
                }
                else if(amount>=1)
                {
                    count++;
                    amount-=1;
                    penny++;
                }
                
            }
            
            printf("%d\n",count);
            break;
        }
        else
        {
            printf("How much is owed?\n");
            change=GetFloat();
        }
    }
    
 
 return 0;
}
