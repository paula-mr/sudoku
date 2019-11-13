#ifndef SUDOKU_CPP
#define SUDOKU_CPP

#include "Sudoku.h"
#include <iostream>

int atribuirCor(Grafo* grafo, int index, unsigned int coresUsadas);

void resolver(Grafo* grafo) {
	unsigned int coresUsadas = 1;
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
		coresUsadas = atribuirCor(grafo, index, coresUsadas);
		qtdNodesColoridos++;
	}
}

int atribuirCor(Grafo* grafo, int index, unsigned int coresUsadas) {
	std::vector<int> cores = grafo->recuperarCoresVizinhas(index);
	std::cout << "b" << index << std::endl;

	if (cores.size() == coresUsadas) {
		coresUsadas++;
		grafo->nodes[index].valor = coresUsadas;
		std::cout << coresUsadas << std::endl;
	} else {
		int cor = 0;

		for (unsigned int i = 0; i <= cores.size(); i++) {
			std::cout << "cor " << cores[i] << " " << std::endl;
		}
		
		for (unsigned int i = 1; i <= coresUsadas && cor == 0; i++) {
			if (!grafo->contem(cores, i))
				cor = i;
		}

		grafo->nodes[index].valor = cor;
		coresUsadas++;
		std::cout << "a" << cor << std::endl;
	}

	grafo->imprimir();

	return coresUsadas;
}

#endif