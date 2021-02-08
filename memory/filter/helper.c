#include "helpers.h"
#include <math.h>
// #include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            int currentPixelAvg = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            currentPixelAvg = round(currentPixelAvg / 3.0);

            image[i][j].rgbtBlue = currentPixelAvg;
            image[i][j].rgbtGreen = currentPixelAvg;
            image[i][j].rgbtRed = currentPixelAvg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    RGBTRIPLE newImage[height][width];
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            int count = 0;
            float sumr = 0, sumg = 0, sumb = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k < 0 || j + l < 0 || i + k >= height || j + l >= width)
                    {
                        continue;
                    }

                    sumr += image[i + k][j + l].rgbtRed;
                    sumg += image[i + k][j + l].rgbtGreen;
                    sumb += image[i + k][j + l].rgbtBlue;

                    count++;
                    // printf("%d %d %d %d - %d %d %f\n", i, j, k, l, count, image[i+k][j+l].rgbtRed, sumr);
                }
            }

            newImage[i][j].rgbtBlue = round(sumb / count);
            newImage[i][j].rgbtGreen = round(sumg / count);
            newImage[i][j].rgbtRed = round(sumr / count);
            // printf("\t\t%d\n", image[i][j].rgbtBlue);
            // scanf("%d", &count);
            // if (count == 5) return;

        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = newImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = newImage[i][j].rgbtGreen;
            image[i][j].rgbtRed = newImage[i][j].rgbtRed;
        }
    }
    return;
}
