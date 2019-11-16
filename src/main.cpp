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

    for (int linha=0; linha<n; linha++) {
        for (int coluna=0; coluna<n; coluna++) {
            int valor = recuperarNumero(arquivo);

            grafo->adicionarAdjacencia(valor, linha, coluna);
        }
    }

    resolver(grafo);

    if (grafo->validarSolucao())
        std::cout << "solução" << std::endl;
    else
        std::cout << "sem solução" << std::endl;

    grafo->imprimir();

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
    int numero = -1, auxiliar;

    //enquanto nao for encontrado um numero valido
    auxiliar = fgetc(arquivo);
    while (numero < 0 && auxiliar != EOF) {
        if (auxiliar != ' ' && auxiliar != '\n') {
            //transforma char em valor numerico
            numero = auxiliar-48;
        }

        auxiliar = fgetc(arquivo);
    }

    return numero;
}