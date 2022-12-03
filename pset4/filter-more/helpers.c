#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t avr;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avr = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avr;
            image[i][j].rgbtGreen = avr;
            image[i][j].rgbtBlue = avr;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < floor(width / 2); j++)
        {
            temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = temp;

            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = temp;

            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //copy
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //corner
            //top right
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtRed =
                    round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed +
                           copy[i + 1][j + 1].rgbtRed) / 4.0);

                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                           copy[i + 1][j + 1].rgbtGreen) / 4.0);

                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j + 1].rgbtBlue) / 4.0);
            }
            //top left
            else if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtRed =
                    round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                           copy[i + 1][j - 1].rgbtRed) / 4.0);

                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                           copy[i + 1][j - 1].rgbtGreen) / 4.0);

                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue) / 4.0);
            }
            //bottom left
            else if (i == height - 1 && j == 0)
            {
                image[i][j].rgbtRed =
                    round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed +
                           copy[i - 1][j + 1].rgbtRed) / 4.0);

                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i - 1][j + 1].rgbtGreen) / 4.0);

                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i - 1][j + 1].rgbtBlue) / 4.0);
            }
            //bottom right
            else if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtRed =
                    round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                           copy[i - 1][j - 1].rgbtRed) / 4.0);

                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i - 1][j - 1].rgbtGreen) / 4.0);

                image[i][j].rgbtBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i - 1][j - 1].rgbtBlue) / 4.0);
            }

            //edge
            //top
            else if (i == 0)
            {
                image[i][j].rgbtRed =
                    round((copy[i][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i][j].rgbtRed +
                           copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);

                image[i][j].rgbtGreen =
                    round((copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                           copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);

                image[i][j].rgbtBlue =
                    round((copy[i][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                           copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            //bottom
            else if (i == height - 1)
            {
                image[i][j].rgbtRed =
                    round((copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j].rgbtRed +
                           copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 6.0);

                image[i][j].rgbtGreen =
                    round((copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                           copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 6.0);

                image[i][j].rgbtBlue =
                    round((copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                           copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 6.0);
            }
            //left
            else if (j == 0)
            {
                image[i][j].rgbtRed =
                    round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j].rgbtRed +
                           copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);

                image[i][j].rgbtGreen =
                    round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j].rgbtGreen +
                           copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);

                image[i][j].rgbtBlue =
                    round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j].rgbtBlue +
                           copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            //right
            else if (j == width - 1)
            {
                image[i][j].rgbtRed =
                    round((copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j].rgbtRed +
                           copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 6.0);

                image[i][j].rgbtGreen =
                    round((copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                           copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 6.0);

                image[i][j].rgbtBlue =
                    round((copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                           copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 6.0);
            }

            //the rest
            else
            {
                image[i][j].rgbtRed =
                    round((copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                           copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed +
                           copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 9.0);

                image[i][j].rgbtGreen =
                    round((copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                           copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 9.0);

                image[i][j].rgbtBlue =
                    round((copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                           copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                           copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 9.0);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int rx, gx, bx, ry, gy, by, r, g, b;

    //copy
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //ggx
            //corner
            //top left
            if (i == 0 && j == 0)
            {
                rx = copy[i][j + 1].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed;
                gx = copy[i][j + 1].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen;
                bx = copy[i][j + 1].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue;
            }
            //top tight
            else if (i == 0 && j == width - 1)
            {
                rx = - copy[i + 1][j - 1].rgbtRed - copy[i][j - 1].rgbtRed * 2;
                gx = - copy[i + 1][j - 1].rgbtGreen - copy[i][j - 1].rgbtGreen * 2;
                bx = - copy[i + 1][j - 1].rgbtBlue - copy[i][j - 1].rgbtBlue * 2;
            }
            //bottom left
            else if (i == height - 1 && j == 0)
            {
                rx = copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed * 2;
                gx = copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen * 2;
                bx = copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue * 2;
            }
            //bottom right
            else if (i == height - 1 && j == width - 1)
            {
                rx = - copy[i - 1][j - 1].rgbtRed - copy[i][j - 1].rgbtRed * 2;
                gx = - copy[i - 1][j - 1].rgbtGreen - copy[i][j - 1].rgbtGreen * 2;
                bx = - copy[i - 1][j - 1].rgbtBlue - copy[i][j - 1].rgbtBlue * 2;
            }

            //edge
            //top
            else if (i == 0)
            {
                rx = copy[i][j + 1].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed -
                     copy[i][j - 1].rgbtRed * 2 - copy[i + 1][j - 1].rgbtRed;
                gx = copy[i][j + 1].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen -
                     copy[i][j - 1].rgbtGreen * 2 - copy[i + 1][j - 1].rgbtGreen;
                bx = copy[i][j + 1].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue -
                     copy[i][j - 1].rgbtBlue * 2 - copy[i + 1][j - 1].rgbtBlue;
            }
            //bottom
            else if (i == height - 1)
            {
                rx = copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed * 2 -
                     copy[i - 1][j - 1].rgbtRed - copy[i][j - 1].rgbtRed * 2;
                gx = copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen * 2 -
                     copy[i - 1][j - 1].rgbtGreen - copy[i][j - 1].rgbtGreen * 2;
                bx = copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue * 2 -
                     copy[i - 1][j - 1].rgbtBlue - copy[i][j - 1].rgbtBlue * 2;
            }
            //left
            else if (j == 0)
            {
                rx = copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed;
                gx = copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen;
                bx = copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue;
            }
            //right
            else if (j == width - 1)
            {
                rx = - copy[i - 1][j - 1].rgbtRed - copy[i][j - 1].rgbtRed * 2 - copy[i + 1][j - 1].rgbtRed;
                gx = - copy[i - 1][j - 1].rgbtGreen - copy[i][j - 1].rgbtGreen * 2 - copy[i + 1][j - 1].rgbtGreen;
                bx = - copy[i - 1][j - 1].rgbtBlue - copy[i][j - 1].rgbtBlue * 2 - copy[i + 1][j - 1].rgbtBlue;
            }

            //the rest
            else
            {
                rx = copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed -
                     copy[i - 1][j - 1].rgbtRed - copy[i][j - 1].rgbtRed * 2 - copy[i + 1][j - 1].rgbtRed;
                gx = copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen -
                     copy[i - 1][j - 1].rgbtGreen - copy[i][j - 1].rgbtGreen * 2 - copy[i + 1][j - 1].rgbtGreen;
                bx = copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue -
                     copy[i - 1][j - 1].rgbtBlue - copy[i][j - 1].rgbtBlue * 2 - copy[i + 1][j - 1].rgbtBlue;
            }

            //ggy
            //corner
            //top left
            if (i == 0 && j == 0)
            {
                ry = copy[i + 1][j].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed;
                gy = copy[i + 1][j].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen;
                by = copy[i + 1][j].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue;
            }
            //top right
            else if (i == 0 && j == width - 1)
            {
                ry = copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed * 2;
                gy = copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen * 2;
                by = copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue * 2;
            }
            //bottom left
            else if (i == height - 1 && j == 0)
            {
                ry = - copy[i - 1][j].rgbtRed * 2 - copy[i - 1][j + 1].rgbtRed;
                gy = - copy[i - 1][j].rgbtGreen * 2 - copy[i - 1][j + 1].rgbtGreen;
                by = - copy[i - 1][j].rgbtBlue * 2 - copy[i - 1][j + 1].rgbtBlue;
            }
            //bottom right
            else if (i == height - 1 && j == width - 1)
            {
                ry = - copy[i - 1][j - 1].rgbtRed - copy[i - 1][j].rgbtRed * 2;
                gy = - copy[i - 1][j - 1].rgbtGreen - copy[i - 1][j].rgbtGreen * 2;
                by = - copy[i - 1][j - 1].rgbtBlue - copy[i - 1][j].rgbtBlue * 2;
            }

            //edge
            //top
            else if (i == 0)
            {
                ry = copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed;
                gy = copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen;
                by = copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue;
            }
            //bottom
            else if (i == height - 1)
            {
                ry = - copy[i - 1][j - 1].rgbtRed - copy[i - 1][j].rgbtRed * 2 - copy[i - 1][j + 1].rgbtRed;
                gy = - copy[i - 1][j - 1].rgbtGreen - copy[i - 1][j].rgbtGreen * 2 - copy[i - 1][j + 1].rgbtGreen;
                by = - copy[i - 1][j - 1].rgbtBlue - copy[i - 1][j].rgbtBlue * 2 - copy[i - 1][j + 1].rgbtBlue;
            }
            //left
            else if (j == 0)
            {
                ry = copy[i + 1][j].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed -
                     copy[i - 1][j].rgbtRed * 2 - copy[i - 1][j + 1].rgbtRed;
                gy = copy[i + 1][j].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen -
                     copy[i - 1][j].rgbtGreen * 2 - copy[i - 1][j + 1].rgbtGreen;
                by = copy[i + 1][j].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue -
                     copy[i - 1][j].rgbtBlue * 2 - copy[i - 1][j + 1].rgbtBlue;
            }
            //right
            else if (j == width - 1)
            {
                ry = copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed * 2 -
                     copy[i - 1][j - 1].rgbtRed - copy[i - 1][j].rgbtRed * 2;
                gy = copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen * 2 -
                     copy[i - 1][j - 1].rgbtGreen - copy[i - 1][j].rgbtGreen * 2;
                by = copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue * 2 -
                     copy[i - 1][j - 1].rgbtBlue - copy[i - 1][j].rgbtBlue * 2;
            }

            //the rest
            else
            {
                ry = copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed -
                     copy[i - 1][j - 1].rgbtRed - copy[i - 1][j].rgbtRed * 2 - copy[i - 1][j + 1].rgbtRed;
                gy = copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen -
                     copy[i - 1][j - 1].rgbtGreen - copy[i - 1][j].rgbtGreen * 2 - copy[i - 1][j + 1].rgbtGreen;
                by = copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue -
                     copy[i - 1][j - 1].rgbtBlue - copy[i - 1][j].rgbtBlue * 2 - copy[i - 1][j + 1].rgbtBlue;
            }

            r = round(sqrt(pow(rx, 2) + pow(ry, 2)));
            g = round(sqrt(pow(gx, 2) + pow(gy, 2)));
            b = round(sqrt(pow(bx, 2) + pow(by, 2)));

            //check if above 255
            if (r > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = r;
            }

            if (g > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = g;
            }

            if (b > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = b;
            }
        }
    }

    return;
}
