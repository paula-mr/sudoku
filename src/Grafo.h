#ifndef GRAFO_H
#define GRAFO_H

#include "Node.h"

class Grafo {

    public:
        Node *nodes;
        int tamanho;
        int colunas;
        int linhas;

        Grafo(Node *nodes, int colunas, int linhas, int tamanho);
        ~Grafo();
        void adicionarAdjacencia(int valor, int k, int l);
        int recuperarGrau(int u);
        int recuperarGrauSaturado(int u);
        std::vector<int> recuperarCoresVizinhas(int u);
        bool validar();
        void imprimir();
};

#endif