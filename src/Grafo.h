#ifndef GRAFO_H
#define GRAFO_H

#include "Node.h"

class Grafo {

    public:
        Node *nodes;
        int tamanho;
        int i;
        int j;

        Grafo(Node *nodes, int i, int j, int tamanho);
        ~Grafo();
        void adicionarAdjacencia(int valor, int k, int l);
        int recuperarGrau(int u);
        int recuperarGrauSaturado(int u);
        std::vector<int> recuperarCoresVizinhas(int u);
        bool contem(std::vector<int> vetor, int elemento);
        void imprimir();
};

#endif