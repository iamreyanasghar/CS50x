#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]){
	if(argc != 2){
                printf("Usage: ./caesar.out key\n");
                return 1;
        }
	int key = atoi(argv[1]);
        string text = get_string("Plaintext: ");
	for(int i = 0; i < strlen(text); i++){
		if(isalpha(text[i])){
			if(islower(text[i])){
				text[i] = (text[i] - 'a' + key) % 26 + 'a';
			}
			else if(isupper(text[i])){
				text[i] = (text[i] - 'A' + key) % 26 + 'A';
			}
		else{
			return 0;
		}
	    }
	}
	printf("Cipher text: %s\n", text);

}
