#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float sumofc, mix;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Adding all the color values
            sumofc = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;

            // Getting the average
            mix = sumofc / 3.0;

            image[i][j].rgbtRed = round(mix);
            image[i][j].rgbtGreen = round(mix);
            image[i][j].rgbtBlue = round(mix);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    for (int i = 0; i < height; i++)
    {
        // Loops until middle pixel
        for (int j = 0; j < width / 2; j++)
        {
            if ((width - 1) - j != 0)
            {
                // Swapping the values
                temp = image[i][j];
                image[i][j] = image[i][(width - 1) - j];
                image[i][(width - 1) - j] = temp;
            }

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float avrgRed, avrgGreen, avrgBlue;
    RGBTRIPLE copyimage[height][width];

    // Copies the pixels from one image to another
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            copyimage[k][l].rgbtRed = image[k][l].rgbtRed;
            copyimage[k][l].rgbtGreen = image[k][l].rgbtGreen;
            copyimage[k][l].rgbtBlue = image[k][l].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumofRed = 0, sumofGreen = 0, sumofBlue = 0, count = 0;

            // If there is any pixels above
            if ((i - 1) >= 0)
            {
                sumofRed += copyimage[i - 1][j].rgbtRed;
                sumofGreen += copyimage[i - 1][j].rgbtGreen;
                sumofBlue += copyimage[i - 1][j].rgbtBlue;
                count++;

                // If there is any pixel on the left(upper row)
                if ((j - 1) >= 0)
                {
                    sumofRed += copyimage[i - 1][j - 1].rgbtRed;
                    sumofGreen += copyimage[i - 1][j - 1].rgbtGreen;
                    sumofBlue += copyimage[i - 1][j - 1].rgbtBlue;
                    count++;
                }

                // If there is any pixel on the right(upper row)
                if ((j + 1) < width)
                {
                    sumofRed += copyimage[i - 1][j + 1].rgbtRed;
                    sumofGreen += copyimage[i - 1][j + 1].rgbtGreen;
                    sumofBlue += copyimage[i - 1][j + 1].rgbtBlue;
                    count++;
                }
            }

            // If there is any pixels below
            if ((i + 1) < height)
            {
                sumofRed += copyimage[i + 1][j].rgbtRed;
                sumofGreen += copyimage[i + 1][j].rgbtGreen;
                sumofBlue += copyimage[i + 1][j].rgbtBlue;
                count++;

                // If there is any pixel on the left(down row)
                if ((j - 1) >= 0)
                {
                    sumofRed += copyimage[i + 1][j - 1].rgbtRed;
                    sumofGreen += copyimage[i + 1][j - 1].rgbtGreen;
                    sumofBlue += copyimage[i + 1][j - 1].rgbtBlue;
                    count++;
                }

                // If there is any pixel on the right(down row)
                if ((j + 1) < width)
                {
                    sumofRed += copyimage[i + 1][j + 1].rgbtRed;
                    sumofGreen += copyimage[i + 1][j + 1].rgbtGreen;
                    sumofBlue += copyimage[i + 1][j + 1].rgbtBlue;
                    count++;
                }
            }

            // If there is any pixels to the left(mid row)
            if ((j - 1) >= 0)
            {
                sumofRed += copyimage[i][j - 1].rgbtRed;
                sumofGreen += copyimage[i][j - 1].rgbtGreen;
                sumofBlue += copyimage[i][j - 1].rgbtBlue;
                count++;
            }

            // If there is any pixels to the right(mid row)
            if ((j + 1) < width)
            {
                sumofRed += copyimage[i][j + 1].rgbtRed;
                sumofGreen += copyimage[i][j + 1].rgbtGreen;
                sumofBlue += copyimage[i][j + 1].rgbtBlue;
                count++;
            }

            // Calculates the main pixel
            sumofRed += copyimage[i][j].rgbtRed;
            sumofGreen += copyimage[i][j].rgbtGreen;
            sumofBlue += copyimage[i][j].rgbtBlue;
            count++;

            // Getting the average
            avrgRed = sumofRed / count;
            avrgGreen = sumofGreen / count;
            avrgBlue = sumofBlue / count;

            // Finally sets the values to the outfile
            image[i][j].rgbtRed = round(avrgRed);
            image[i][j].rgbtGreen = round(avrgGreen);
            image[i][j].rgbtBlue = round(avrgBlue);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyimage[height][width];

    // Copies the pixels from one image to another
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            copyimage[k][l].rgbtRed = image[k][l].rgbtRed;
            copyimage[k][l].rgbtGreen = image[k][l].rgbtGreen;
            copyimage[k][l].rgbtBlue = image[k][l].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float GxRed = 0, GxGreen = 0, GxBlue = 0, GyRed = 0, GyGreen = 0, GyBlue = 0;

            if ((i - 1) >= 0)
            {
                GyRed -= (2 * copyimage[i - 1][j].rgbtRed);
                GyGreen -= (2 * copyimage[i - 1][j].rgbtGreen);
                GyBlue -= (2 * copyimage[i - 1][j].rgbtBlue);

                if ((j - 1) >= 0)
                {
                    GxRed -= (1 * copyimage[i - 1][j - 1].rgbtRed);
                    GxGreen -= (1 * copyimage[i - 1][j - 1].rgbtGreen);
                    GxBlue -= (1 * copyimage[i - 1][j - 1].rgbtBlue);

                    GyRed -= (1 * copyimage[i - 1][j - 1].rgbtRed);
                    GyGreen -= (1 * copyimage[i - 1][j - 1].rgbtGreen);
                    GyBlue -= (1 * copyimage[i - 1][j - 1].rgbtBlue);
                }

                if ((j + 1) < width)
                {
                    GxRed += (1 * copyimage[i - 1][j + 1].rgbtRed);
                    GxGreen += (1 * copyimage[i - 1][j + 1].rgbtGreen);
                    GxBlue += (1 * copyimage[i - 1][j + 1].rgbtBlue);

                    GyRed -= (1 * copyimage[i - 1][j + 1].rgbtRed);
                    GyGreen -= (1 * copyimage[i - 1][j + 1].rgbtGreen);
                    GyBlue -= (1 * copyimage[i - 1][j + 1].rgbtBlue);
                }
            }

            // Checks if there is any pixels below
            if ((i + 1) < height)
            {
                GyRed += (2 * copyimage[i + 1][j].rgbtRed);
                GyGreen += (2 * copyimage[i + 1][j].rgbtGreen);
                GyBlue += (2 * copyimage[i + 1][j].rgbtBlue);

                if ((j - 1) >= 0)
                {
                    GxRed -= (1 * copyimage[i + 1][j - 1].rgbtRed);
                    GxGreen -= (1 * copyimage[i + 1][j - 1].rgbtGreen);
                    GxBlue -= (1 * copyimage[i + 1][j - 1].rgbtBlue);

                    GyRed += (1 * copyimage[i + 1][j - 1].rgbtRed);
                    GyGreen += (1 * copyimage[i + 1][j - 1].rgbtGreen);
                    GyBlue += (1 * copyimage[i + 1][j - 1].rgbtBlue);

                }

                if ((j + 1) < width)
                {
                    GxRed += (1 * copyimage[i + 1][j + 1].rgbtRed);
                    GxGreen += (1 * copyimage[i + 1][j + 1].rgbtGreen);
                    GxBlue += (1 * copyimage[i + 1][j + 1].rgbtBlue);

                    GyRed += (1 * copyimage[i + 1][j + 1].rgbtRed);
                    GyGreen += (1 * copyimage[i + 1][j + 1].rgbtGreen);
                    GyBlue += (1 * copyimage[i + 1][j + 1].rgbtBlue);

                }
            }

            // Checks if there is any pixels to the left
            if ((j - 1) >= 0)
            {
                GxRed -= (2 * copyimage[i][j - 1].rgbtRed);
                GxGreen -= (2 * copyimage[i][j - 1].rgbtGreen);
                GxBlue -= (2 * copyimage[i][j - 1].rgbtBlue);

            }

            // Checks if there is any pixels to the right
            if ((j + 1) < width)
            {
                GxRed += (2 * copyimage[i][j + 1].rgbtRed);
                GxGreen += (2 * copyimage[i][j + 1].rgbtGreen);
                GxBlue += (2 * copyimage[i][j + 1].rgbtBlue);

            }

            // Assighning the red value
            if (round(sqrt(pow(GxRed, 2) + pow(GyRed, 2))) < 255)
            {
                image[i][j].rgbtRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }

            // Assighning the Green value
            if (round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2))) < 255)
            {
                image[i][j].rgbtGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }

            // Assighning the Blue value
            if (round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2))) < 255)
            {
                image[i][j].rgbtBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }
    return;
}