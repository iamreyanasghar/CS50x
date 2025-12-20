#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // String Declaration 
    char *s = "HI!";
    printf("%s\n", s);

    // Pointers as a String
    printf("%p\n", s);
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);

    // Pointer Arithmetic
    printf("%c\n", s[0]);
    printf("%c\n", s[1]);
    printf("%c\n", s[2]);
}
