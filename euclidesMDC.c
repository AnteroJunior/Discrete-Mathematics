#include <stdio.h>

/*

ACCORDING TO EUCLIDES GREATEST COMMON DIVISOR ALGORITHM
WE CAN FIND IT USING THE FOLLOWING METHOD:

-- WHILE THE MODULE IS DIFFERENT FROM ZERO, WE KEEP EXECUTING THE GCD FUNCTION

# gcd(a, b) -> b = a * quotient + remainder

and gcd(remainder, a) is equivalent to gcd(a, b)

#gcd(a, r) -> a = remainder * quotient + newRemainder

PS: IN BRAZIL WE CALL MÁXIMO DIVISOR COMUM (MDC).

PS: numberA is the lowest and numberB is the greatest.

*/

//PROTOTYPES
int getMDC(int numberA, int numberB, int remainder, int lastRemainder);

int main(){

	int numberA, numberB;

		printf("Informe os números A e B: ");

		scanf("%d %d", &numberA, &numberB);

	int lastRemainder, remainder, MDC;

	if(numberA > numberB){

		if(numberA % numberB == 0){

			printf("MDC(%d, %d) = %d\n", numberA, numberB, numberB);			

		} else {

			MDC = getMDC(numberB, numberA, remainder, lastRemainder);

			printf("MDC(%d, %d) = %d\n", numberA, numberB, MDC);

		}

	} else if(numberA < numberB){

		if(numberB % numberA == 0){

			printf("MDC(%d, %d) = %d\n", numberA, numberB, numberA);	

		} else {

			MDC = getMDC(numberA, numberB, remainder, lastRemainder);

			printf("MDC(%d, %d) = %d\n", numberA, numberB, MDC);

		}

	} else {

		printf("MDC(%d, %d) = %d\n", numberA, numberA, numberA);

	}

	return 0;

}

int getMDC(int numberA, int numberB, int remainder, int lastRemainder){

	remainder = (numberB % numberA);

	if(remainder == 0){//WE SHOULD RETURN THE LASTREMAINDER NOT EQUAL TO ZERO

		return lastRemainder;

	} else {

		lastRemainder = remainder;

		return getMDC(remainder, numberA, remainder, lastRemainder);

	}

}