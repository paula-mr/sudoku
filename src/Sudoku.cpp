#ifndef SUDOKU_CPP
#define SUDOKU_CPP

#include "Sudoku.h"
#include "Util.h"

void atribuirCor(Grafo* grafo, int index);

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
			if (!contem(cores, i))
				cor = i;
		}

		grafo->nodes[index].valor = cor;
	}
}

#endif