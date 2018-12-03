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

SkewNode* criarNovoNo(int chave) {
	SkewNode* new_skew_node = (SkewNode*) malloc(sizeof(SkewNode));
	new_skew_node->chave = chave;
	new_skew_node->subArvoreEsquerda = NULL;
	new_skew_node->subArvoreDireita = NULL;
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

void printProfundidade(SkewNode* no) {
	int h = calcularAltura(no);
	int i;
	for (i=1; i<=h; i++){
		imprimirNivel(no, i);
	}
}

SkewHeap* criarSkewHeap() {
	SkewHeap* new_skew_heap = (SkewHeap*) malloc(sizeof(SkewHeap));
	new_skew_heap->noRaiz = NULL;
	return new_skew_heap;
}

void alternarFilhos(SkewNode* no) {
	SkewNode* noEmTroca = no->subArvoreDireita;
	no->subArvoreDireita = no->subArvoreEsquerda;
	no->subArvoreEsquerda = noEmTroca;
}

void adicionarNoDireita(SkewNode* noHeap, SkewNode* noTransferencia) {
	noHeap->subArvoreDireita = noTransferencia;
	alternarFilhos(noHeap);
}

void mesclarNo(SkewNode* noEsquerda, SkewNode* noDireita) {
	if (noEsquerda->chave <= noDireita->chave) {
		if (noEsquerda->subArvoreDireita == NULL) {
			adicionarNoDireita(noEsquerda, noDireita);
		}
	}
}

void adicionarNo(int chave) {
	SkewNode* novoNo = criarNovoNo(chave);
	mesclarNo(noRaiz, novoNo);
}

int main(void) {
	noRaiz = criarNovoNo(40);
	adicionarNo(80);
	printProfundidade(noRaiz);
	return EXIT_SUCCESS;
}
