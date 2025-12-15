#include <stdio.h>
#include <cs50.h>

int main(void){
	int n;
	int r = 0;
	
	do{
		n = get_int("Changed Owed: ");
	}while(n < 0);
	while(n >= 25){
		n = n - 25;
		r++;
	}
	while(n >= 10){
		n = n - 10;
		r++;
	}
	while(n >= 5){
		n = n - 5;
		r++;
	}
	while(n > 0){
		n = n - 1;
		r++;
	}
	printf("%i\n", r);
}
