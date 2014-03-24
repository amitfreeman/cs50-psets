/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"


/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    //implementing binary search
    
    int min=0,max=n,mid;
    while(min<=max)
    {
        mid= (min+max)/2;
        
        if(values[mid] == value)
            return true;
        
        else if(values[mid] > value)
            max=mid-1;
            
        else if(values[mid] < value)
            min=mid+1;
    }
    
    return false;
}




/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Implementing insertion sort
    for(int i=1; i<n ; i++)
    {
        //marking current element
        int E = values[i]; 
        int j=i; 
        
        //comparing current element with previous numbers which are assumed sorted 
        //if previous is greater, array is shifted to right to make space for element
        while( values[j-1]>E && j>0)
        {
            values[j]=values[j-1];
            j--;
        }
        
        values[j]=E;
    }
    
    return;
}
