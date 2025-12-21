#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;
    for(int i = 0; i < height; i++){
    	for(int j = 0; j < width; j++){
		avg = (int) round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
		image[i][j].rgbtRed = avg;
		image[i][j].rgbtBlue = avg;
		image[i][j].rgbtGreen = avg;
	}
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaBlue;
    int sepiaGreen;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
		sepiaRed = (int) round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
		sepiaGreen = (int) round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
		sepiaBlue = (int) round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);     		
		if(sepiaRed > 255){
			sepiaRed = 255;
		}
		if(sepiaBlue > 255){
                        sepiaBlue = 255;
                }
		if(sepiaGreen > 255){
                        sepiaGreen = 255;
		}
		
		image[i][j].rgbtRed = sepiaRed;
		image[i][j].rgbtBlue = sepiaBlue;
		image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    
    int tmpRed, tmpBlue, tmpGreen;
    int overwidth = 0;

    if(overwidth % 2 == 0){
    	overwidth = width / 2;
    }
    else{
    	overwidth = width / 2 + 1;
    }

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < overwidth; j++)
        {
            // Swap pixels
		tmp[i][j] = image[i][j];
		image[i][j] = image[i][width - 1 -j];
		image[i][width - 1 -j] = tmp[i][j];
        }
    }
    return;
}

// Blur image
// AI generated due to its complex concept
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float tmpRed = 0, tmpBlue = 0, tmpGreen = 0;
            float pixelcount = 0;
            
            // Check 3x3 neighborhood around current pixel
            for (int y = -1; y <= 1; y++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    int new_i = i + y;
                    int new_j = j + x;
                    
                    // Check if new position is within image bounds
                    if (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width)
                    {
                        tmpRed += image[new_i][new_j].rgbtRed;
                        tmpBlue += image[new_i][new_j].rgbtBlue;
                        tmpGreen += image[new_i][new_j].rgbtGreen;
                        pixelcount++;
                    }
                }
            }
            
            // Calculate average for this pixel
            tmp[i][j].rgbtRed = (int)round(tmpRed / pixelcount);
            tmp[i][j].rgbtBlue = (int)round(tmpBlue / pixelcount);
            tmp[i][j].rgbtGreen = (int)round(tmpGreen / pixelcount);
        }
    }
    
    // Copy blurred image back to original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
}
