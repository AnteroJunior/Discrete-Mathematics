#include <stdio.h>
#include <math.h>
#include <stdbool.h>

//PROTÓTIPOS
bool isPrime(int number, int startAnalysis);
int getMMC(int numberA, int numberB, int fatorPrimo, int MMC);
int getMDC(int numberA, int numberB, int fatorPrimo, int MDC);

int main(){

	int numberA, numberB;

	printf("Informe os valores do número A e do número B: ");
	
		scanf("%d %d", &numberA, &numberB);

	//VERIFICAR SE SÃO IGUAIS
	if(numberA == numberB){

		printf("MMC(%d, %d) = %d  MDC(%d, %d) = %d\n", numberA, numberB, numberA, numberA, numberB, numberA);

	} else if(isPrime(numberA, 2) && isPrime(numberB, 2)){//SE FOREM PRIMOS ENTRE SI

		printf("MMC(%d, %d) = %d  MDC(%d, %d) = 1\n", numberA, numberB, getMMC(numberA, numberB, 2, 1), numberA, numberB);

	} else {

		printf("MMC(%d, %d) = %d  MDC(%d, %d) = %d\n", numberA, numberB, getMMC(numberA, numberB, 2, 1), numberA, numberB, getMDC(numberA, numberB, 2, 1));

	}

	return 0;

}

//MMC começando com 1, porque é multiplicação || fatorPrimo é o número que vai dividir
int getMMC(int numberA, int numberB, int fatorPrimo, int MMC){

	//ENQUANTO MAIORES QUE 1, CONTINUAMOS A VERIFICAÇÃO
	if(numberA > 1 || numberB > 1){

		if(isPrime(fatorPrimo, 2)){

			if(numberA % fatorPrimo == 0 && numberB % fatorPrimo == 0){

				MMC *= fatorPrimo;

				numberA /= fatorPrimo;
				numberB /= fatorPrimo;

				//ENQUANTO O FATOR PRIMO DIVIDIR UM DOS DOIS OU OS DOIS, CONTINUA COM ELE
				return getMMC(numberA, numberB, fatorPrimo, MMC);

			} else if(numberA % fatorPrimo == 0){//QUANDO SOMENTE ELE É DIVISÍVEL PELO PRIMO

				MMC *= fatorPrimo;

				numberA /= fatorPrimo;//NUMERO SERÁ IGUAL AO VALOR DA DIVISÃO

				return getMMC(numberA, numberB, fatorPrimo, MMC);

			} else if(numberB % fatorPrimo == 0){

				//O MESMO QUE ACONTECE NO A

				MMC *= fatorPrimo;

				numberB /= fatorPrimo;

				return getMMC(numberA, numberB, fatorPrimo, MMC);

			} else {

				return getMMC(numberA, numberB, fatorPrimo + 1, MMC);//QUANDO O FATOR NÃO DIVIDE MAIS NINGUÉM, VERIFICAMOS OUTRO VALOR

			}

		} else {

			return getMMC(numberA, numberB, fatorPrimo + 1, MMC);//QUANDO FATOR PRIMO NÃO É PRIMO

		}

	} else {

		return MMC;

	}

}

int getMDC(int numberA, int numberB, int fatorPrimo, int MDC){

	if(numberA > 1 && numberB > 1){//ENQUANTO OS VALORES FOREM MAIORES QUE UM, CONTINUA

		if(isPrime(fatorPrimo, 2)){//VERIFICANDO SE O FATOR PRIMO É PRIMO

			if(numberA % fatorPrimo == 0 && numberB % fatorPrimo == 0){//MDC É OBSERVADO QUANDO MULTIPLICA OS DOIS

				MDC *= fatorPrimo;//MULTIPLICA

				numberA /= fatorPrimo;//NOVO VALOR DE A
				numberB /= fatorPrimo;//NOVO VALOR DE B

				return getMDC(numberA, numberB, fatorPrimo, MDC);

			} else {//QUANDO SÓ DIVIDE UM OU NENHUM, DIVIDE O VALOR E PASSA O NOVO

				if(numberA % fatorPrimo == 0){

					numberA /= fatorPrimo;

					return getMDC(numberA, numberB, fatorPrimo, MDC);

				} if(numberB % fatorPrimo == 0){

					numberB /= fatorPrimo;

					return getMDC(numberA, numberB, fatorPrimo, MDC);

				} else {

					return getMDC(numberA, numberB, fatorPrimo + 1, MDC);

				}

			}

		} else {

			return getMDC(numberA, numberB, fatorPrimo + 1, MDC);//QUANDO O FATOR NÃO É PRIMO

		}

	} else {

		return MDC;

	}

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
