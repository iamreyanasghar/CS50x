#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);
	
    float L = letters/words*100;
    float S = sentences/words*100;

    // Compute the Coleman-Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Print the grade level
    if(index > 16){
    	printf("Grade 16+\n");
    }
    else if(index < 2){
    	printf("Before Grade 1\n");
    }
    else{
    	printf("Grade %i\n", (int)index);
    }
}

int count_letters(string text)
{
    // Return the number of letters in text
	int n = 0;
	for(int i = 0; i < strlen(text); i++){
		if(text[i] != ' '){
			n  = n + 1;
		}
	}
	return n;
}

int count_words(string text)
{
    // Return the number of words in text
	int n = 1;
	for(int i = 0; i < strlen(text); i++){
		if(text[i] == ' '){
			n = n + 1;
		}
	}
	return n;
}

int count_sentences(string text)
{
    // Return the number of sentences in text
	int n = 0;
	for(int i = 0; i < strlen(text); i++){
		if(text[i] == '.' || text[i] == '?' || text[i] == '!'){
			n = n + 1;
		}
	}
	return n;
}


