#ifndef SUDOKU_CPP
#define SUDOKU_CPP

#include "Sudoku.h"
#include <iostream>

void atribuirCor(Grafo* grafo, int index);
int encontrarMaiorValor(std::vector<int> vetor);

void resolver(Grafo* grafo) {
	int qtdNodesColoridos = 0;
	int tamanho = grafo->tamanho*grafo->tamanho;


	while (qtdNodesColoridos < tamanho) {
		int max = -1;
		int index = -1;

		for (int i = 0; i < tamanho; i++) {
			if (grafo->nodes[i].valor == 0) {
				int grauSaturacao = grafo->recuperarGrauSaturado(i);
				if (grauSaturacao > max) {
					max = grauSaturacao;
					index = i;
				}
				else if (grauSaturacao == max) {
					if (grafo->recuperarGrau(i) > grafo->recuperarGrau(index)) {
						index = i;
					}
				}
			}
		}

		if (grafo->nodes[index].valor == 0)
			atribuirCor(grafo, index);

		qtdNodesColoridos++;

		/*std::cout << index << std::endl;
		grafo->imprimir();*/
	}
}

void atribuirCor(Grafo* grafo, int index) {
	std::vector<int> cores = grafo->recuperarCoresVizinhas(index);
	unsigned int maiorValor = encontrarMaiorValor(cores);

	if (cores.size() == maiorValor) {
		grafo->nodes[index].valor = maiorValor+1;
	} else {
		int cor = 0;
		
		for (int i = 1; i <= grafo->tamanho && cor == 0; i++) {
			if (!grafo->contem(cores, i))
				cor = i;
		}

		grafo->nodes[index].valor = cor;
	}
}


int encontrarMaiorValor(std::vector<int> vetor) {
	int max = vetor[0];
	for (unsigned int i=1; i < vetor.size(); i++) {
		if (vetor[i] > max) {
			max = vetor[i];
		}
	}

	return max;
}

#endif