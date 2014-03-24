/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Author : Amit Paropkari
 * Date : 22-03-2014
 *
 * It resizes BMP image by factor of n , where n is between 1 to 100.
 *
 * 24-03-2014
 * // updated, for biHeight parameter , as it is not always negative for .bmp images.
 *
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

     int digit_flag = 0, n=0;
      
    //check if first argument is integer number
  
    for(int i=0, len=strlen(argv[1]); i < len ; i++)
    {
        if(isdigit(argv[1][i]))
            digit_flag = 1;
        else
        {
            printf("Usage: ./resize n infile outfile , where n is positive integer\n");
            return 2;
        }    
    }
    
    if(digit_flag == 1)
    {
        n = atoi(argv[1]);
        if(n < 1 || n > 100)
        {
            printf("resize value n should be between 1 to 100\n");
            return 3;
        }
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, new_bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    //copy into new header variable
    new_bf = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, new_bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    //copy into new header variable
    new_bi = bi;
    
        // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    //Calculate new parameters- image size, file size to be written to resized image
    LONG new_biWidth = n * bi.biWidth;
    LONG new_biHeight = n * abs(bi.biHeight);
    
    //calculate infile's padding in bytes 
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // calculate padding required for outfile in bytes
    int new_padding = (4 - (new_biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //calculate tota size in bytes , fileheader + infoheader + (pixel + padding x pixel)
    DWORD  new_bfSize = 54 + (((new_biWidth* 3) + new_padding) * new_biHeight);
    
   printf("new_biWidth %d new_biWidth %d padding %d new_padding %d new_bfSize %d\n",new_biWidth,new_biHeight,padding,new_padding,new_bfSize);

   //modify in variables bf and bi
    new_bf.bfSize = new_bfSize;
    new_bi.biWidth = new_biWidth;
    //check if bi.biHeight is positive or negative
    if(bi.biHeight < 0)
        new_bi.biHeight =  - new_biHeight; 
    else
        new_bi.biHeight =  new_biHeight;   
        
    new_bi.biSizeImage = (new_biWidth * new_biHeight) * 3;

    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);


   // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
            //store the row in form of triples
            RGBTRIPLE arr[new_biWidth];
            int pos=0;
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times in a row
                for(int a=0 ; a<n ; a++)
                {
                    arr[pos++] = triple;
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);  
                }      
              
            }

             // then add padding to optput file, if any
             for (int k = 0; k < new_padding; k++)
             {
                 fputc(0x00, outptr);
             }
            
            //now add this row n-1 times, as already added once
            for(int b=0 ; b < n-1 ; b++)
            {
                fwrite(arr, sizeof(arr), 1, outptr);
              // then add padding to optput file for that line, if any
                 for (int k = 0; k < new_padding; k++)
                 {
                     fputc(0x00, outptr);
                 }
            }
            
            
            // skip over padding in input file, if any
            fseek(inptr, padding, SEEK_CUR);

    }



    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
