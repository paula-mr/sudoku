#ifndef SUDOKU_CPP
#define SUDOKU_CPP

#include "Sudoku.h"
#include <iostream>

int atribuirCor(Grafo* grafo, int index, unsigned int coresUsadas);

void resolver(Grafo* grafo) {
	unsigned int coresUsadas = 1;
	int tamanho = grafo->tamanho*grafo->tamanho;

	while (grafo->quantidadeNodesColoridos < tamanho) {
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

		coresUsadas = atribuirCor(grafo, index, coresUsadas);
		grafo->incrementarNodesColoridos();
	}

}

int atribuirCor(Grafo* grafo, int index, unsigned int coresUsadas) {
	std::vector<int> cores = grafo->recuperarCoresVizinhas(index);

	if (cores.size() == coresUsadas) {
		coresUsadas++;
		grafo->nodes[index].valor = coresUsadas;
		std::cout << coresUsadas << std::endl;
	} else {
		int cor = 0;
		
		for (int i = 1; i <= grafo->tamanho && cor == 0; i++) {
			if (!grafo->contem(cores, i))
				cor = i;
		}

		grafo->nodes[index].valor = cor;
	}

	return coresUsadas;
}

#endif