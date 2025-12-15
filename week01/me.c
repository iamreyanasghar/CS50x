#include <stdio.h>
#include <cs50.h>

int main(void)
{
	string name = get_string("Enter Your Name: ");
	printf("Hello, %s\n", name);
}
