/*
 ============================================================================
 Name        : skewheap.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "skewheap.h"

SkewNode* noRaiz;

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

void swapSubArvores(SkewNode* subArvoreDireita,SkewNode* noHeapTransferencia){
	noHeapTransferencia->pai = subArvoreDireita->pai;
	subArvoreDireita->pai = NULL;
	noHeapTransferencia->pai->subArvoreDireita = noHeapTransferencia;
}

void mesclarNo(SkewNode* noEsquerda, SkewNode* noDireita) {
	if (noEsquerda->chave <= noDireita->chave) {
		if (noEsquerda->subArvoreDireita == NULL) {
			adicionarNoDireita(noEsquerda, noDireita);
		} else {
			swapFilhos(noEsquerda);
			mesclarNo(noEsquerda->subArvoreDireita, noDireita);
		}
	} else {
		swapSubArvores(noEsquerda, noDireita);
		swapFilhos(noDireita);
		mesclarNo(noDireita, noEsquerda);
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
	for (i = 1; i < argc; i++) {
		char *teste = argv[i];
		int w;
		sscanf(teste, "%d", &w);
		sequenciaNos[i-1] = w;
	}
}

int main(int argc, char* argv[]) {
	printf("%i\n", argc);
	int sequenciaNos[argc-1];
	transformarChavesEntrada(argv, argc, sequenciaNos);
	int chaveNoRaiz = sequenciaNos[0];
	noRaiz = criarNovoNo(chaveNoRaiz, NULL);
	int j;
	for (j = 1; j < argc-1; j++) {
		int chave = sequenciaNos[j];
		printf("%i \n", chave);
		adicionarNo(chave);
	}
	imprimirProfundidade(noRaiz);


	return EXIT_SUCCESS;
}
