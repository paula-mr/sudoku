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
};

#endif