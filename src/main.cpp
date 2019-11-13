#include <stdio.h>
#include <iostream>

#include "Grafo.h"
#include "Sudoku.h"

FILE* abrirArquivo(int argc, char *argv[]);
int recuperarNumero(FILE* arquivo);

int main(int argc, char *argv[]) {

    FILE* arquivo = abrirArquivo(argc, argv);
    if (arquivo == NULL)
        return 1;

    int n, i, j;

    n = recuperarNumero(arquivo);
    i = recuperarNumero(arquivo);
    j = recuperarNumero(arquivo);
    
    Node nodes[n*n];
    Grafo* grafo = new Grafo(nodes, i, j, n);

    for (int k=0; k<n; k++) {
        for (int l=0; l<n; l++) {
            int valor = recuperarNumero(arquivo);

            grafo->adicionarAdjacencia(valor, k, l);
        }
    }

    resolver(grafo);

    for (int k=0; k<n; k++) {
        for (int l=0; l<n; l++) {
            int posicao = k*n + l;
            std::cout << grafo->nodes[posicao].valor << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

FILE* abrirArquivo(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Parâmetro inválido.";
        return NULL;
    }

    char* nomeArquivo = argv[1];

    FILE* arquivo = fopen(nomeArquivo, "r");

    return arquivo;
}

int recuperarNumero(FILE* arquivo) {
    int numero = 0, auxiliar;

    //enquanto char lido nao for espaco branco ou nova linha
    while ((auxiliar = fgetc(arquivo)) != ' ' && auxiliar != '\n' && auxiliar != EOF) {
        numero*=10;
        //transforma char em valor numerico
        numero+=auxiliar-48;
    }

    return numero;
}