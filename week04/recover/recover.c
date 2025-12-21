#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *file = fopen(argv[1], "r");
    FILE *img = NULL;
    
    int found = 1;
    int counter = 0;
    char filename[8];

    // Create a buffer for a block of data
    uint8_t buffer[512];

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, file) == 512)
    {
        // Create JPEGs from the data
	if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
		found = 0;	
    	}
	if(found == 0){
		if(counter != 0){
			fclose(img);
		}
		sprintf(filename, "%03i.jpg", counter);
		counter ++;
		img = fopen(filename, "w");
		fwrite(buffer, 1, 512, img);
		found = 1;
	}
	else if (counter != 0){
		fwrite(buffer, 1, 512, img);
	}
    }
    fclose(img);
    fclose(file);
}
