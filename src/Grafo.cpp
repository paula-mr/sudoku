#ifndef GRAFO_CPP
#define GRAFO_CPP

#include "Grafo.h"

#include <iostream>
#include <algorithm>

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
    while (posicao + i*tamanho < tamanho*tamanho) {
        nodes[posicao].adjacencias.push_back(posicao + i*tamanho);
        nodes[posicao + i*tamanho].adjacencias.push_back(posicao);
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

    for (unsigned int i=0; i < nodes[u].adjacencias.size(); i++) {
        int adjacencia = nodes[u].adjacencias[i];
        if (nodes[adjacencia].valor != 0 && !contem(elementosUnicos, nodes[adjacencia].valor)) {
            elementosUnicos.push_back(nodes[adjacencia].valor);
        }
    }

    return elementosUnicos;
}

bool Grafo::contem(std::vector<int> vetor, int elemento) {
    return (std::find(vetor.begin(), vetor.end(), elemento) != vetor.end());
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