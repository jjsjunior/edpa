/*
 * skewheap.h
 *
 *  Created on: 3 de dez de 2018
 *      Author: jones
 */

#ifndef SKEWHEAP_H_
#define SKEWHEAP_H_


struct skew_heap_node_struct {
	int  chave;
	struct skew_heap_node_struct* subArvoreEsquerda,*subArvoreDireita, *pai;
};

typedef struct skew_heap_node_struct SkewNode;

struct skew_heap_struct {
	SkewNode* noRaiz;
};

typedef struct skew_heap_struct SkewHeap;

SkewNode* criarNovoNo(int s, SkewNode* pai);


#endif /* SKEWHEAP_H_ */
