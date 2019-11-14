#ifndef GRAFO_CPP
#define GRAFO_CPP

#include "Grafo.h"
#include "Util.h"

#include <iostream>
#include <algorithm>

Grafo::Grafo(Node *nodes, int colunas, int linhas, int tamanho) {
    this->nodes = nodes;
    this->colunas = colunas;
    this->linhas = linhas;
    this->tamanho = tamanho;
}

Grafo::~Grafo() = default;

void Grafo::adicionarAdjacencia(int valor, int linha, int coluna) {
    int posicao = linha*tamanho + coluna;
    nodes[posicao].valor = valor;
    //adiciona proximas adjacencias verticais
    int i = 1;
    while (posicao + i*tamanho < tamanho*tamanho) {
        nodes[posicao].adjacencias.push_back(posicao + i*tamanho);
        nodes[posicao + i*tamanho].adjacencias.push_back(posicao);
        i++;
    }

    //adiciona proximas adjacencias horizontais
    int j = 1;
    while (posicao + j < tamanho*(linha+1)) {
        nodes[posicao].adjacencias.push_back(posicao + j);
        nodes[posicao + j].adjacencias.push_back(posicao);
        j++;
    }

    //adiciona proximas adjacencias do quadrante
    i = linha + 1;

    //define coluna inicial do quadrante
    j = coluna + 1;
    while (j%colunas != 0) {
        j++;
    }
    j -= colunas;

    while (i%linhas != 0) {
        int posicaoQuadrante = i*tamanho + j;

        if (j != coluna){
            nodes[posicao].adjacencias.push_back(posicaoQuadrante);
            nodes[posicaoQuadrante].adjacencias.push_back(posicao);
        }
        j++;

        if (j%colunas == 0) {
            j -= colunas;
            i++;
        }
    }
}

int Grafo::recuperarGrau(int u) {
    return nodes[u].adjacencias.size();
}

int Grafo::recuperarGrauSaturado(int u) {
    int grau = 0;
    std::vector<int> elementosUnicos;

    for (unsigned int i=0; i < nodes[u].adjacencias.size(); i++) {
        int adjacencia = nodes[u].adjacencias[i];
        if (nodes[adjacencia].valor != 0 && !contem(elementosUnicos, nodes[adjacencia].valor)) {
            grau++;
            elementosUnicos.push_back(nodes[nodes[u].adjacencias[i]].valor);
        }
    }
    return grau;
}

std::vector<int> Grafo::recuperarCoresVizinhas(int u) {
    std::vector<int> elementosUnicos;

    //percorre as cores vizinhas adjacentes
    for (unsigned int i=0; i < nodes[u].adjacencias.size(); i++) {
        int adjacencia = nodes[u].adjacencias[i];
        if (nodes[adjacencia].valor != 0 && !contem(elementosUnicos, nodes[adjacencia].valor)) {
            elementosUnicos.push_back(nodes[adjacencia].valor);
        }
    }
    
    return elementosUnicos;
}

bool Grafo::validar() {
    for (int k=0; k<tamanho*tamanho; k++) {
        if (nodes[k].valor == 0 || nodes[k].valor > tamanho)
            return false;
    }

    return true;
}

void Grafo::imprimir() {
    for (int k=0; k<tamanho; k++) {
        for (int l=0; l<tamanho; l++) {
            int posicao = k*tamanho + l;
            std::cout << nodes[posicao].valor << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

#endif