#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            double grey = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue);
            int gray = round(grey / 3);
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
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            int red = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int green = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int blue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
void swap(RGBTRIPLE *p, RGBTRIPLE *q)
{
    RGBTRIPLE temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float redTotal = 0;
    float greenTotal = 0;
    float blueTotal = 0;
    float counter = 0;

    RGBTRIPLE tmp[height][width];

    //iterate through each row of the image h times
    for (int i = 0; i < height; i++)
    {
        //loop copying ith image row into tmp
        for (int j = 0; j < width; j++)
        {
            //assign image at ith & jth index to tmp variable
            tmp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            //middle row
            //mid mid
            redTotal = tmp[i][j].rgbtRed;
            greenTotal = tmp[i][j].rgbtGreen;
            blueTotal = tmp[i][j].rgbtBlue;
            counter = 1;

            //mid left
            if (j - 1 >= 0)
            {
                redTotal += tmp[i][j - 1].rgbtRed;
                greenTotal += tmp[i][j - 1].rgbtGreen;
                blueTotal += tmp[i][j - 1].rgbtBlue;
                counter++;
            }

            // mid right
            if (j < width - 1)
            {
                redTotal += tmp[i][j + 1].rgbtRed;
                greenTotal += tmp[i][j + 1].rgbtGreen;
                blueTotal += tmp[i][j + 1].rgbtBlue;
                counter++;
            }

            //upper row
            if (i - 1 >= 0)
            {
                //upper mid
                redTotal += tmp[i - 1][j].rgbtRed;
                greenTotal += tmp[i - 1][j].rgbtGreen;
                blueTotal += tmp[i - 1][j].rgbtBlue;
                counter++;

                //upper left
                if (j - 1 >= 0)
                {
                    redTotal += tmp[i - 1][j - 1].rgbtRed;
                    greenTotal += tmp[i - 1][j - 1].rgbtGreen;
                    blueTotal += tmp[i - 1][j - 1].rgbtBlue;
                    counter++;
                }

                //upper right
                if (j < width - 1)
                {
                    redTotal += tmp[i - 1][j + 1].rgbtRed;
                    greenTotal += tmp[i - 1][j + 1].rgbtGreen;
                    blueTotal += tmp[i - 1][j + 1].rgbtBlue;
                    counter++;
                }
            }

            //lower row
            if (i + 1 <= height)
            {
                //lower mid
                redTotal += tmp[i + 1][j].rgbtRed;
                greenTotal += tmp[i + 1][j].rgbtGreen;
                blueTotal += tmp[i + 1][j].rgbtBlue;
                counter++;

                //lower left
                if (j - 1 >= 0)
                {
                    redTotal += tmp[i + 1][j - 1].rgbtRed;
                    greenTotal += tmp[i + 1][j - 1].rgbtGreen;
                    blueTotal += tmp[i + 1][j - 1].rgbtBlue;
                    counter++;
                }

                //lower right
                if (j < width - 1)
                {
                    redTotal += tmp[i + 1][j + 1].rgbtRed;
                    greenTotal += tmp[i + 1][j + 1].rgbtGreen;
                    blueTotal += tmp[i + 1][j + 1].rgbtBlue;
                    counter++;
                }
            }


            //assign avg values to RGB of pixel
            image[i][j] = (RGBTRIPLE)
            {
                .rgbtBlue = round((int)blueTotal / counter), .rgbtGreen = round((int)greenTotal / counter),
                .rgbtRed = round((int)redTotal / counter)

            };

        }
    }
}