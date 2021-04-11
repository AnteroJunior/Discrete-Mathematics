#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/* 

AS WE KNOW, A NUMBER IS PRIME IF EXISTS A NUMBER LESS THAN OR IGUAL TO SQUARE ROOT OF THAT NUMBER 
SO WE CAN SEARCH AND TEST UNTIL WE REACH THE SQUARE ROOT 

*/

bool isPrime(int number, int startCount){

	if(startCount <= sqrt(number)){

		if(number % startCount == 0){//IF MOD IGUAL TO ZERO THEN NUMBER IS NOT PRIME

			return false;

		} else {

			isPrime(number, startCount + 1);

		}

	} else {

		return true;//IS PRIME

	}

}

int main(){

	int number, startCount = 2;

		printf("Insert the number you want to verify: ");

		scanf("%d", &number);

	bool prime = isPrime(number, startCount);

	if(prime == true){

		puts("It is a prime number!");

	} else {

		puts("It is not a prime number!");

	}


	return 0;

}