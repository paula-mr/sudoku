#ifndef SUDOKU_CPP
#define SUDOKU_CPP

#include "Sudoku.h"
#include "Util.h"

void atribuirCor(Grafo* grafo, int indice);
int selecionarProximoIndice(Grafo* grafo);

void resolver(Grafo* grafo) {
	int quantidadeNodesColoridos = 0;
	int tamanho = grafo->tamanho*grafo->tamanho;


	while (quantidadeNodesColoridos < tamanho) {
		int indice = selecionarProximoIndice(grafo);
		if (indice > -1)
			atribuirCor(grafo, indice);
		quantidadeNodesColoridos++;
	}
}

int selecionarProximoIndice(Grafo* grafo) {
	int maximo = -1;
	int indice = -1;
	int tamanho = grafo->tamanho*grafo->tamanho;

	for (int i = 0; i < tamanho; i++) {
		if (grafo->nodes[i].valor == 0) {
			//armazena quantos vizinhos coloridos o node possui
			int grauSaturacao = grafo->recuperarGrauSaturado(i);
			if (grauSaturacao > maximo) {
				maximo = grauSaturacao;
				indice = i;
			}
		}
	}

	return indice;
}

void atribuirCor(Grafo* grafo, int indice) {
	std::vector<int> cores = grafo->recuperarCoresVizinhas(indice);
	unsigned int maiorValor = encontrarMaiorValor(cores);

	if (cores.size() == maiorValor) {
		grafo->nodes[indice].valor = maiorValor+1;
	} else {
		int cor = 0;
		
		for (int i = 1; i <= grafo->tamanho && cor == 0; i++) {
			if (!contem(cores, i))
				cor = i;
		}

		grafo->nodes[indice].valor = cor;
	}
}

#endif