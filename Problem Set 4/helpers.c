#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //average the values of three integers by 3.0 and round float numbers to neartest integer when assigning them to a pixel value
    int gray = 0;
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            gray = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0);
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //max allowable value is 255
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            image[i][j].rgbtRed = min(round(0.393*image[i][j].rgbtRed + 0.769*image[i][j].rgbtGreen + 0.189*image[i][j].rgbtBlue), 255);
            image[i][j].rgbtGreen = min(round(0.349*image[i][j].rgbtRed + 0.686*image[i][j].rgbtGreen + 0.168*image[i][j].rgbtBlue), 255);
            image[i][j].rgbtBlue = min(round(0.272*image[i][j].rgbtRed + 0.534*image[i][j].rgbtGreen + 0.131*image[i][j].rgbtBlue), 255);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int buffer;
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width/2; j++)
        {
            buffer = image[i][j];
            image[i][j] = image[i][width-1-j];
            image[i][width-1-j] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of image
    //declare a new 2d array with RGBTRIPLE copy [height][width]
    //copy image into copy, pixel by pixel with nested for loops
    //then read pixel colors from copy but write pixel's colors in image
    int sumBlue;
    int sumGreen;
    int sumRed;
    float counter;

    RGBtriple copy[height][width];

    int average;

    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            counter = 0.0;

            for(int k =-1; k<2; k++)
            {
                if(i+k < 0 || i+k > height -1)
                {
                    continue;
                }

                for (int h = -1; h<2; h++)
                {
                    if (j+h <0 || j+h > width-1)
                    {
                        continue;
                    }

                    sumBlue += image[i+k][j+h].rgbtBlue;
                    sumGreen += image[i+k][j+h].rgbtGreen;
                    sumRed += image[i+k][j+h].rgbtRed;
                    counter++;
                }
            }

            temp[i][j].rgbtBlue = round(sumBlue/counter);
            temp[i][j].rgbtGreen = round(sumGreen/counter);
            temp[i][j].rgbtRed = round(sumRed/counter);
        }
    }

    for (int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
