#include <cs50.h>
#include <stdio.h>

void print_row(int bricks);
void print_spaces(int s);

int main(void)
{
    // Prompt the user for the pyramid's height
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    // Print a pyramid of that height
    for (int i = 0; i < n; i++)
    {
	print_spaces(n-(i+1));
        // Print row of bricks
        print_row(i + 1);
    }
}

void print_row(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}

void print_spaces(int s){
	for(int i = s; i > 0; i--){
		printf(" ");
	}
}
