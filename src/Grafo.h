#ifndef GRAFO_H
#define GRAFO_H

#include "Node.h"

class Grafo {

    public:
        Node *nodes;
        int tamanho;
        int quantidadeColunas;
        int quantidadeLinhas;

        Grafo(Node *nodes, int quantidadeColunas, int quantidadeLinhas, int tamanho);
        ~Grafo();
        void adicionarAdjacencia(int valor, int linha, int coluna);
        int recuperarGrau(int posicao);
        int recuperarGrauSaturado(int posicao);
        std::vector<int> recuperarCoresVizinhas(int posicao);
        void imprimir();

        bool validarSolucao();
        bool validarLinha(int linha);
        bool validarColuna(int coluna);
        bool validarQuadrante(int linhaInicial, int colunaInicial);
        bool validarPosicao(int linha, int coluna);
};

#endif