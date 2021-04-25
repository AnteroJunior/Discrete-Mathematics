import time
import math
import sys

sys.setrecursionlimit(1500) # COMPLETE RECURSION WITHOUT ERRORS

def main():

	showPrimes()


def showPrimes():

	value = 2

	tempoInicio = time.time()

	while(time.time() - tempoInicio < 60):

		if(isPrime(value, 2)):

			print(value)

			value = value + 1

		else:

			value = value + 1

def isPrime(number, count):

	if(count <= math.sqrt(number)):

		if(number % count == 0):

			return False

		else:

			return isPrime(number, count + 1)

	else:

		return True	


main()