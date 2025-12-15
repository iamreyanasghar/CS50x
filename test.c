#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void){
	int key = 13;
	char text[] = "Hi there!";
	for(int i = 0; i < strlen(text); i++){
		if(text[i] != '\0'){
			text[i] = text[i] + key - 26;
		} 
	}
	printf("%s\n", text);
}
