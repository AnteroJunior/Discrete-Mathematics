#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isPrime(int number, int startAnalysis);
void decomposeNumber(int number, int startDiv);


int main(){

	int number, startDiv = 2;

		scanf("%d", &number);

	if(isPrime(number, 2)){

		puts("Cannot decompose number because it is a prime number");

		printf("It is divided by 1 and %d\n", number);

	} else {

		decomposeNumber(number, 2);

	}

	return 0;

}

bool isPrime(int number, int startAnalysis){

	if(startAnalysis <= sqrt(number)){

		if(number % startAnalysis == 0){

			return false;

		} else {

			isPrime(number, startAnalysis + 1);

		}

	} else {

		return true;

	}

}

void decomposeNumber(int number, int startDiv){

	if(number != 1){

		if(isPrime(startDiv, 2)){//SE O DIVISOR FOR PRIMO

			if(number % startDiv == 0){

				printf("%d ", startDiv);

				number /= startDiv;

				decomposeNumber(number, startDiv);

			} else {

				decomposeNumber(number, startDiv + 1);

			}

		} else {//SE DIVISOR NÃO FOR PRIMO

			decomposeNumber(number, startDiv + 1);

		}

	} else {

		puts("");

		return;

	}

}