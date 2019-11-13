#ifndef GRAFO_CPP
#define GRAFO_CPP

#include "Grafo.h"
#include <iostream>

Grafo::Grafo(Node *nodes, int i, int j, int tamanho) {
    this->nodes = nodes;
    this->i = i;
    this->j = j;
    this->tamanho = tamanho;
}

Grafo::~Grafo() = default;

void Grafo::adicionarAdjacencia(int valor, int k, int l) {
    int posicao = k*tamanho + l;
    nodes[posicao].valor = valor;

    //adiciona proximas adjacencias verticais
    int i = 1;
    while (i*tamanho < tamanho*tamanho) {
        nodes[posicao].adjacencias.push_back(posicao + i*tamanho);
        nodes[l + i*tamanho].adjacencias.push_back(posicao);
        i++;
    }

    //adiciona proximas adjacencias horizontais
    int j = 1;
    while (posicao + j < tamanho*(k+1)) {
        nodes[posicao].adjacencias.push_back(posicao + j);
        nodes[posicao + j].adjacencias.push_back(posicao);
        j++;
    }
}

int Grafo::recuperarGrau(int u) {
    return nodes[u].adjacencias.size();
}

#endif