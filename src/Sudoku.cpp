#ifndef SUDOKU_CPP
#define SUDOKU_CPP

#include "Sudoku.h"
#include "Util.h"

void atribuirCor(Grafo* grafo, int indice);
int selecionarProximoIndice(Grafo* grafo);
int selecionarMelhorCor(Grafo* grafo, std::vector<int> coresVizinhas);

bool resolver(Grafo* grafo) {
	while (!grafo->estaCompleto()) {
		int indice = selecionarProximoIndice(grafo);
		atribuirCor(grafo, indice);
	}

	return true;
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
			} else if (grauSaturacao == maximo && grafo->recuperarGrau(i) > grafo->recuperarGrau(indice)) {
				maximo = grauSaturacao;
				indice = i;
			}
		}
	}
	return indice;
}

void atribuirCor(Grafo* grafo, int indice) {
	std::vector<int> coresVizinhas = grafo->recuperarCoresVizinhas(indice);
	grafo->nodes[indice].valor = selecionarMelhorCor(grafo, coresVizinhas);
}


int selecionarMelhorCor(Grafo* grafo, std::vector<int> coresVizinhas) {
	std::vector<int> coresPossiveis;
	int contagem[grafo->tamanho+1];
    int maiorValor = 0;
    int cor = 0;

    //seleciona cores possiveis
    for (int i = 1; i < grafo->tamanho+1; i++) {
        contagem[i] = 0;
        if (!contem(coresVizinhas, i)) {
            coresPossiveis.push_back(i);
        }
    }

    if (coresPossiveis.size() == 0)
    	return grafo->tamanho+1;

    if (coresPossiveis.size() == 1)
        return coresPossiveis[0];

    //realiza contagem de quantidade de cada cor no sudoku
    cor = coresPossiveis[0];
	for (int i = 0; i < grafo->tamanho*grafo->tamanho; i++) {
		if (grafo->nodes[i].valor != 0 && grafo->nodes[i].valor < grafo->tamanho+1) {
			contagem[grafo->nodes[i].valor] = contagem[grafo->nodes[i].valor]+1;
		}
	}

	//seleciona cor que mais aparece
	for (unsigned int i = 0; i < coresPossiveis.size(); i++) {
		if (contagem[coresPossiveis[i]] > maiorValor) {
			cor = coresPossiveis[i];
			maiorValor = contagem[coresPossiveis[i]];
		}
	}

	return cor;
}


#endif