/*
 ============================================================================
 Name        : skewheap.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "skewheap.h"
#include <string.h>
#include <time.h>

SkewNode* noRaiz;
int qtdComparacoes = 0;

SkewNode* criarNovoNo(int chave, SkewNode* pai) {
	SkewNode* new_skew_node = (SkewNode*) malloc(sizeof(SkewNode));
	new_skew_node->chave = chave;
	new_skew_node->subArvoreEsquerda = NULL;
	new_skew_node->subArvoreDireita = NULL;
	new_skew_node->pai = pai;
	return new_skew_node;
}

int calcularAltura(SkewNode* no) {
	if (no == NULL)
		return 0;
	else {
		int alturaEsquerda = calcularAltura(no->subArvoreEsquerda);
		int alturaDireita = calcularAltura(no->subArvoreDireita);
		if (alturaEsquerda > alturaDireita)
			return (alturaEsquerda + 1);
		else
			return (alturaDireita + 1);
	}
}

void imprimirNivel(SkewNode* no, int nivel) {
	if (no == NULL)
		return;
	if (nivel == 1)
		printf("%i ", no->chave);
	else if (nivel > 1) {
		imprimirNivel(no->subArvoreEsquerda, nivel - 1);
		imprimirNivel(no->subArvoreDireita, nivel - 1);
	}
}

void imprimirProfundidade(SkewNode* no) {
	int h = calcularAltura(no);
	int i;
	for (i = 1; i <= h; i++) {
		imprimirNivel(no, i);
	}
	printf("\n ");
}

SkewHeap* criarSkewHeap() {
	SkewHeap* new_skew_heap = (SkewHeap*) malloc(sizeof(SkewHeap));
	new_skew_heap->noRaiz = NULL;
	return new_skew_heap;
}

void swapFilhos(SkewNode* no) {
	SkewNode* noEmTroca = no->subArvoreDireita;
	no->subArvoreDireita = no->subArvoreEsquerda;
	no->subArvoreEsquerda = noEmTroca;
}

void adicionarNoDireita(SkewNode* noHeap, SkewNode* noTransferencia) {
	noHeap->subArvoreDireita = noTransferencia;
	noTransferencia->pai = noHeap;
	swapFilhos(noHeap);
}

void swapSubArvores(SkewNode* subArvoreDireita, SkewNode* noHeapTransferencia) {
	if (subArvoreDireita->pai == NULL && noHeapTransferencia->pai == NULL) { //caso nenhuma das 2 subarvores tenha pai se trata de um swap dos dois heaps
		noRaiz = noHeapTransferencia;
	} else {
		noHeapTransferencia->pai = subArvoreDireita->pai;
		subArvoreDireita->pai = NULL;
		if (noHeapTransferencia->pai != NULL) {
			noHeapTransferencia->pai->subArvoreDireita = noHeapTransferencia;
		}
	}
}

void mesclarNo(SkewNode* noEsquerda, SkewNode* noDireita) {
	qtdComparacoes++;
	if (noEsquerda->chave <= noDireita->chave) {
		if (noEsquerda->subArvoreDireita == NULL) {
			adicionarNoDireita(noEsquerda, noDireita);
		} else {
			swapFilhos(noEsquerda);
			if (noEsquerda->subArvoreDireita == NULL) {
						adicionarNoDireita(noEsquerda, noDireita);
			} else{
				mesclarNo(noEsquerda->subArvoreDireita, noDireita);
			}
		}
	} else {
		swapSubArvores(noEsquerda, noDireita);
		swapFilhos(noDireita);
		mesclarNo(noDireita, noEsquerda);
	}
}

void gerarChaves(int int_min, int int_max, int quantidadeNos, int arrayChaves[]) {
	int i;
	for (i = 0; i < quantidadeNos; i++) {
		int num = (rand() % (int_max - int_min + 1)) + int_min;
		arrayChaves[i] = num;
//		printf("%d ", num);
	}
}

void adicionarNo(int chave) {
	SkewNode* novoNo = criarNovoNo(chave, NULL);
	mesclarNo(noRaiz, novoNo);
}

void imprimirEntrada(int argc, char* argv[]) {
	int i;
	for (i = 1; i < argc; i++) {
		char *teste = argv[i];
		printf("%s\n", argv[i]);
		printf("%s\n", teste);
		int i;
		sscanf(teste, "%d", &i);
		printf("%i\n", i);
	}
}

void transformarChavesEntrada(char* argv[], int argc, int sequenciaNos[]) {
	int i;
	for (i = 2; i < argc; i++) {
		char *teste = argv[i];
		int w;
		sscanf(teste, "%d", &w);
		printf("%i\n", w);
		sequenciaNos[i - 2] = w;
	}
}

void removerNoMinimo(SkewNode* node){
	if(node->subArvoreDireita!=NULL){
		node->subArvoreDireita->pai = NULL;
	}
	if(node->subArvoreEsquerda != NULL){
		node->subArvoreEsquerda->pai = NULL;
	}
	if(node->subArvoreEsquerda!=NULL){
		noRaiz = node->subArvoreEsquerda;
	} else if (node->subArvoreDireita!=NULL){
		noRaiz = node->subArvoreEsquerda;
	} else {
		noRaiz = NULL;
	}
	if(noRaiz!=NULL && node->subArvoreEsquerda!=NULL && node->subArvoreDireita!=NULL){
		mesclarNo(node->subArvoreEsquerda, node->subArvoreDireita);
	}
	free(node);
}


void desconstruirHeap(){
	removerNoMinimo(noRaiz);
	if(noRaiz!=NULL){
		desconstruirHeap();
	}
}

void executarAmbienteDesenvolvimento(int argc, char* argv[]) {
	int sequenciaNos[argc - 2];
	transformarChavesEntrada(argv, argc, sequenciaNos);
	int chaveNoRaiz = sequenciaNos[0];
	noRaiz = criarNovoNo(chaveNoRaiz, NULL);
	int j;
	for (j = 1; j < argc - 2; j++) {
		int chave = sequenciaNos[j];
//		printf("%i \n", chave);
		adicionarNo(chave);
	}
	printf("\n %s \n", "imprimir arvore");
	imprimirProfundidade(noRaiz);

	qtdComparacoes = 0;
	printf("%s\n", "iniciando remocoes");
	clock_t t;
	t = clock();
	desconstruirHeap();
	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
	printf("foram gastos %f segundos para descontruir arvore \n", time_taken);
	printf("\n foram realizadas %d comparações para desconstruir a arvore \n", qtdComparacoes);


}

void imprimirArray(int qtdItems, int array[]) {
	int j;
	for (j = 0; j < qtdItems; j++) {
		printf("%d ", array[j]);
	}
}



void executarAmbienteProducao(int argc, char* argv[]) {
	char *n = argv[2];
	int quantidadeNos;
	sscanf(n, "%d", &quantidadeNos);
	printf("%s\n", "qtde de nos: ");
	printf("%i\n", quantidadeNos);

	char *minimo = argv[3];
	int intMin;
	sscanf(minimo, "%d", &intMin);
	printf("%s\n", "INT_MIN: ");
	printf("%i\n", intMin);

	char *maximo = argv[4];
	int intMax;
	sscanf(maximo, "%d", &intMax);
	printf("%s\n", "INT_MAX: ");
	printf("%i\n", intMax);
	int arrayChaves[quantidadeNos];
	gerarChaves(intMin, intMax, quantidadeNos, arrayChaves);
//	imprimirArray(quantidadeNos, arrayChaves);
	clock_t t;
	t = clock();
	int chaveNoRaiz = arrayChaves[0];
	noRaiz = criarNovoNo(chaveNoRaiz, NULL);
	int chaveAtual;
	for (chaveAtual = 1; chaveAtual < quantidadeNos; chaveAtual++) {
		int chave = arrayChaves[chaveAtual];
//		printf("%i \n", chave);
		adicionarNo(chave);
	}
	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
	printf("foram gastos %f segundos para construir arvore \n", time_taken);
	printf("%s\n", "imprimir arvore");
	int altura = calcularAltura(noRaiz);
	printf("\no skewheap possui altura %d \n", altura);
	printf("\n foram realizadas %d comparações para construir a arvore \n", qtdComparacoes);
	qtdComparacoes = 0;
	printf("%s\n", "iniciando remocoes");
	t = clock();
	desconstruirHeap();
	t = clock() - t;
	time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
	printf("foram gastos %f segundos para descontruir arvore \n", time_taken);
	printf("\n foram realizadas %d comparações para desconstruir a arvore \n", qtdComparacoes);

//	imprimirProfundidade(noRaiz);

}

int main(int argc, char* argv[]) {
//	printf("%i\n", argc);
	char *ambiente = argv[1];
	printf("%s\n", ambiente);
	if (strcmp("d", ambiente) == 0) {
		executarAmbienteDesenvolvimento(argc, argv);
	} else {
		executarAmbienteProducao(argc, argv);

	}

	return EXIT_SUCCESS;
}
