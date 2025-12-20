#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{

    // Get two strings
    char *s = get_string("s: ");
    char *t = get_string("t: ");

    // Compare strings' addresses
    if (s == t)
    {
        printf("Same Adressess\n");
    }
    else
    {
        printf("Different Adressess\n");
    }

    // Compare strings
    if (strcmp(s, t) == 0)
    {
        printf("Same Strings\n");
    }
    else
    {
        printf("Different Strings\n");
    }

}
