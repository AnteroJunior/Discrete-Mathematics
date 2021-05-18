#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

//PROTÓTIPOS
void menu();
bool ehPrimo(int, int);
int verificaMDC(int, int, int, int);
void geraChavePublica(int, int);
void verificaMensagem(char[], int, int);
int potenciacaoModularRapida(int, int, int);
void decriptarMensagem(int, int, int);
int pegaInverso(int, int, int);

int main(){

	int menuOpcao, p, q, e, p_q;

	while(1){

		menu();

		scanf("%d", &menuOpcao);

		puts("");

		if(menuOpcao == 1){

			puts("***** INFORME P, Q e E PARA GERAR A SUA CHAVE (p q e)*****\n");

				scanf("%d %d %d", &p, &q, &e);

			puts("");

			//VAMOS VERIFICAR SE 'P', 'Q' E 'E' SÃO PRIMOS
			if(ehPrimo(p, 2) && ehPrimo(q, 2) && ehPrimo(e, 2)){

				//2: PRIMO QUE COMEÇA A VERIFICAÇÃO - 1: VALOR INICIAL DA MULTIPLICAÇÃO
				if(verificaMDC(e, (p - 1) * (q - 1), 2, 1) == 1){

					puts("***** VALORES VÁLIDOS! A CHAVE PÚBLICA SERÁ GERADA EM SEGUIDA *****\n");

					geraChavePublica(e, p * q);

				} else {

					puts("***** VALOR DE 'E' NÃO COPRIMO A '(P-1) * (Q-1)'. TENTE NOVAMENTE *****\n");

				}

			} else {

				puts("***** VERIFIQUE OS VALORES E TENTE NOVAMENTE *****\n");

			}

		} else if(menuOpcao == 2){

			char mensagem[3000];

			puts("***** INFORME A MENSAGEM QUE SERÁ ENCRIPTADA *****");

				getchar();

			//A MENSAGEM SERÁ LIDA ATÉ O USUÁRIO DIGITAR \n
			scanf("%[^\n]s", mensagem);

			//AGORA A MENSAGEM SERÁ ANALISADA E ENCRIPTADA
			puts("***** INFORME OS DOIS VALORES RECEBIDOS ('E' 'P*Q') DA CHAVE PÚBLICA *****\n");

				scanf("%d %d", &e, &p_q);

			puts("");

			verificaMensagem(mensagem, e, p_q);

		} else if(menuOpcao == 3){

			puts("***** PARA DECRIPTAR SUA MENSAGEM, INFORME 'P', 'Q' E 'E' QUE FORMAM A CHAVE PÚBLICA\n");

			scanf("%d %d %d", &p, &q, &e);

			decriptarMensagem(p, q, e);

		} else if(menuOpcao == 0){

			break;

		} else {

			puts("***** OPÇÃO NÃO ENCONTRADA *****\n");

		}

	}

	return 0;
}


void geraChavePublica(int e, int pq){

	FILE *pntPublicKey = fopen("publicKey.txt", "w");

	fprintf(pntPublicKey, "%d %d", e, pq);

	fclose(pntPublicKey);

}

void verificaMensagem(char mensagem[], int e, int pq){

	FILE *pntEncrypted = fopen("encrypted.txt", "w");

	int i = 0, newNumber = 0;

	int tamMensagem = strlen(mensagem);

	while(i <= tamMensagem){

		if(mensagem[i] == ' ' || mensagem[i] == '\0' || mensagem[i] == '\n'){

			newNumber = 28 * 100;

		} else {

			newNumber = (int)mensagem[i] - 65 + 2;
			newNumber = newNumber * 100;
			
		}

		if(mensagem[i + 1] == ' ' || mensagem[i + 1] == '\0' || mensagem[i + 1] == '\n'){

			newNumber = newNumber + 28;

			newNumber = potenciacaoModularRapida(newNumber, e, pq);

			fprintf(pntEncrypted, " %d ", newNumber);

		} else {

			newNumber = newNumber + ((int)mensagem[i + 1] - 65 + 2);

			newNumber = potenciacaoModularRapida(newNumber, e, pq);

			fprintf(pntEncrypted, " %d ", newNumber);

		}

		i = i + 2;

	}

	puts("***** MENSAGEM ENCRIPTADA COM SUCESSO! VERIFIQUE O ARQUIVO 'encrypted.txt'\n");

	fclose(pntEncrypted);

}

/*
a: numero
b: expoente
m: modulo
*/
int potenciacaoModularRapida(int a, int b, int m){

    a %= m;

    int res = 1;

    while (b > 0) {

        if (b & 1){   //impar  (& operador bitwise and)

            res = res * a % m;  //o mesmo que (res % m) * (a % m)

		}

        a = a * a % m;

        b >>= 1;   // /2 ( >> operador bitwise shift)

    }

    return res;
}

void decriptarMensagem(int p, int q, int e){

	FILE *pntEncrypted = fopen("encrypted.txt", "r");
	FILE *pntDecrypted = fopen("decrypted.txt", "w");

	int mod_inverso = (p - 1) * (q - 1);
	int mod = p * q;

	if(verificaMDC(e, mod, 2, 1) == 1){

		//São coprimos
		int inverso = pegaInverso(e, mod_inverso, 1);

		int valueAch, num1, num2;

		while(!feof(pntEncrypted)){

			fscanf(pntEncrypted, " %d ", &valueAch);

			valueAch = potenciacaoModularRapida(valueAch, inverso, mod);

			if(valueAch / 100 == 28){

				fprintf(pntDecrypted, " ");

			} else {

				num1 = (valueAch / 100) - 2 + 65;

				fprintf(pntDecrypted, "%c", (char)num1);

			}

			if(valueAch % 100 == 28){

				fprintf(pntDecrypted, " ");

			} else {

				num2 = (valueAch % 100) - 2 + 65;

				fprintf(pntDecrypted, "%c", (char)num2);


			}

		}

		puts("");

		fclose(pntEncrypted);
		fclose(pntDecrypted);

		puts("***** A MENSAGEM FOI DECRIPTADA. VERIFIQUE O ARQUIVO 'decrypted.txt' PARA VER A MENSAGEM *****");

	} else {

		puts("***** NÃO É POSSÍVEL DECRIPTAR COM ESSES NÚMEROS *****\n");

	}

}

int pegaInverso(int exp, int mod, int count){

	if(count < mod){

		int valor = (exp * count) % mod;

		if(valor == 1){

			return count;

		} else {

			return pegaInverso(exp, mod, count + 1);

		}

	}

}

void menu(){

	char asterisco[] = "*********";

	printf("%9s MENU %9s\n", asterisco, asterisco);

	puts("*1. Gerar chave pública*");
	puts("*2. Encriptar mensagem *");
	puts("*3. Decriptar mensagem *");
	puts("*0. Parar execução     *");

	puts("************************\n");

}

bool ehPrimo(int number, int primeCount){

	if(primeCount <= sqrt(number)){

		if(number % primeCount == 0){

 			return false;

		} else {

			ehPrimo(number, primeCount + 1);

		}

	} else {

		return true;

	}

}

int verificaMDC(int numA, int numB, int inicioPrimo, int valorMDC){

	if(numA > 1 && numB > 1){

		if(ehPrimo(inicioPrimo, 2)){

			if(numA % inicioPrimo == 0 && numB % inicioPrimo == 0){//AMBOS DIVIDIDOS

				valorMDC *= inicioPrimo;

				numA /= inicioPrimo;
				numB /= inicioPrimo;

				return verificaMDC(numA, numB, inicioPrimo, valorMDC);

			} else {//ALGUM OU NENHUM É DIVIDIDO

				if(numA % inicioPrimo == 0){

					numA /= inicioPrimo;

					return verificaMDC(numA, numB, inicioPrimo, valorMDC);

				} else if(numB % inicioPrimo == 0){

					numB /= inicioPrimo;

					return verificaMDC(numA, numB, inicioPrimo, valorMDC);

				} else {

					return verificaMDC(numA, numB, inicioPrimo + 1, valorMDC);

				}

			}

		} else {

			return verificaMDC(numA, numB, inicioPrimo + 1, valorMDC);

		}

	} else {

		return valorMDC;

	}

}