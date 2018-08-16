	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <windows.h>
	#include <conio.h>
	#include <locale.h>
	#include <limits.h>
	#include <math.h>
	#define tam 200000

	//Codigo escrito e rodado no Visual Studio

	void cores(int ForgC, int BackC) { //cor do texto
		WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
		return;
	}

	void textcolor(int newcolor) { //cor do texto
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		(csbi.wAttributes & 0xf0) | newcolor);
	}

	void duracao(clock_t begin, clock_t end) {
		double duracao = ((double)(end - begin)) / CLOCKS_PER_SEC;
		printf("\nTempo gasto %5.4lfs.\n", duracao);
	}

	void merge(int vetor[], int comeco, int meio, int fim) {
		int com1 = comeco, com2 = meio + 1, comAux = 0, t = fim - comeco + 1;
		int *vetAux;
		vetAux = (int*)malloc(t * sizeof(int));

		while (com1 <= meio && com2 <= fim) {
			if (vetor[com1] < vetor[com2]) {
				vetAux[comAux] = vetor[com1];
				com1++;
			}
			else {
				vetAux[comAux] = vetor[com2];
				com2++;
			}
			comAux++;
	}

	while (com1 <= meio) { 
		vetAux[comAux] = vetor[com1];
		comAux++;
		com1++;
	}

	while (com2 <= fim) {
		vetAux[comAux] = vetor[com2];
		comAux++;
		com2++;
	}

	for (comAux = comeco; comAux <= fim; comAux++) { 
		vetor[comAux] = vetAux[comAux - comeco];
	}

	free(vetAux);
	}

	void mergeSort(int vetor[], int comeco, int fim) {
		clock_t begin = clock();
		if (comeco < fim) {
			int meio = (fim + comeco) / 2;

			mergeSort(vetor, comeco, meio);
			mergeSort(vetor, meio + 1, fim);
			merge(vetor, comeco, meio, fim);
		}

		
	}

	void bubbleSort(int A[]) {
		clock_t begin = clock();
		int i, j, aux;
		for (i = 1; i < tam; i++) {
			for (j = 0; j < tam - 1; j++) {
				if (A[j] > A[j + 1]) {
					aux = A[j];
					A[j] = A[j + 1];
					A[j + 1] = aux;

				}
			}
		}
		clock_t end = clock();
		duracao(begin, end);
	}

	void insertionSort(int A[]) {
		clock_t begin = clock();
		int i, j, temp;
		for (j = 1; j < tam; j++) {
			temp = A[j];
			i = j - 1;
			while (i >= 0 && A[i] < temp) {
				A[i + 1] = A[i];
				i = i - 1;
			}
			A[i + 1] = temp;
		}
		clock_t end = clock();
		duracao(begin, end);
	}

	void selectionSort(int A[]) {
		clock_t begin = clock();
		int i, j, min, aux;
		for (i = 0; i < (tam - 1); i++) {
			min = i;
			for (j = (i + 1); j < tam; j++) {
				if (A[j] < A[min]) {
					min = j;
				}
			}
			aux = A[min];
			A[min] = A[i];
			A[i] = aux;
		}
		clock_t end = clock();
		duracao(begin, end);
	}

	void print(int *A) {
		int n = 2;
		do {
			printf("\nMostrar o exemplo de elementos ? 1 para Sim, 0 para Nao: ");
			scanf_s("%d", &n);
		} while (n != 1 && n != 0);

		if (n == 1) {
			int i;
			printf("\n");
			for (i = 0; i < 200; i++) {
				printf("%03d ", A[i]);
			}
			printf("....");
			for (i = tam; i > tam-200; i--) {
				printf("%03d ", A[i]);
			}
			printf("\n");
			system("pause");
		}
	}

	void gerador(int vetor[]) {
		srand(time(NULL));
		int i;
		printf("\nGerando %d numeros aleatorios...\n", tam);
		printf("Imprimindo os 30 primeiros...\n");
	
		for (i = 0; i < tam; i++) {
			vetor[i] = rand() % 999 + 1;
			if (i < 30){
				textcolor(rand()%15+1);
				printf("%d ", vetor[i]);
			}
		}
		textcolor(15);
		printf("\n");
	}

	int main() {
		int vetor[tam];
		int menu;

		do {
			system("cls");
			gerador(vetor);
			printf("===> Selecionar o metodo de ordenacao <===\n\n");
			printf("1 Bubble Sort\n");
			printf("2 Insertion Sort\n");
			printf("3 Selection Sort\n");
			printf("4 Merge Sort\n");
			printf("0 Sair: ");
			scanf_s("%d", &menu);

			clock_t begin = clock();

			switch (menu) {
			case 1:
				bubbleSort(vetor);
				print(vetor);
				break;
			case 2:
				insertionSort(vetor);
				print(vetor);
				break;
			case 3:
				selectionSort(vetor);
				print(vetor);
				break;
			case 4:
				mergeSort(vetor, 0, tam - 1);
				clock_t end = clock();
				duracao(begin, end);
				print(vetor);
				break;
			case 0:
				break;
				system("pause");
			}
		} while (menu != 0);
	}
