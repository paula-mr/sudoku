#ifndef GRAFO_CPP
#define GRAFO_CPP

#include "Grafo.h"
#include "Util.h"

#include <iostream>
#include <algorithm>

#include <bits/stdc++.h> 

Grafo::Grafo(Node *nodes, int quantidadeColunas, int quantidadeLinhas, int tamanho) {
    this->nodes = nodes;
    this->quantidadeColunas = quantidadeColunas;
    this->quantidadeLinhas = quantidadeLinhas;
    this->tamanho = tamanho;
}

Grafo::~Grafo() = default;

bool Grafo::estaCompleto() {
    for (int i = 0; i < tamanho*tamanho; i++) {
        if (nodes[i].valor == 0)
            return false;
    }

    return true;
}

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
    while (j%quantidadeColunas != 0) {
        j++;
    }
    j -= quantidadeColunas;

    while (i%quantidadeLinhas != 0) {
        int posicaoQuadrante = i*tamanho + j;

        if (j != coluna){
            nodes[posicao].adjacencias.push_back(posicaoQuadrante);
            nodes[posicaoQuadrante].adjacencias.push_back(posicao);
        }
        j++;

        if (j%quantidadeColunas == 0) {
            j -= quantidadeColunas;
            i++;
        }
    }
}

int Grafo::recuperarGrauSaturado(int posicao) {
    std::vector<int> elementosUnicos = recuperarCoresVizinhas(posicao);
    return elementosUnicos.size();
}

std::vector<int> Grafo::recuperarCoresVizinhas(int posicao) {
    std::vector<int> elementosUnicos;

    //percorre as cores vizinhas adjacentes
    for (unsigned int i=0; i < nodes[posicao].adjacencias.size(); i++) {
        int adjacencia = nodes[posicao].adjacencias[i];
        if (nodes[adjacencia].valor != 0 && !contem(elementosUnicos, nodes[adjacencia].valor)) {
            elementosUnicos.push_back(nodes[adjacencia].valor);
        }
    }
    
    return elementosUnicos;
}

bool Grafo::validarLinha(int linha) { 
    std::vector<int> numerosJaVistos; 
  
    for (int i = 0; i < tamanho; i++) { 
  		int posicao = linha*tamanho + i;

  		//se o numero atual ja foi visto, retorna falso
        if (contem(numerosJaVistos, nodes[posicao].valor)) 
            return false; 

        if (nodes[posicao].valor == 0 || nodes[posicao].valor > tamanho)
            return false;

        numerosJaVistos.push_back(nodes[posicao].valor);

    } 
    return true; 
} 
  
bool Grafo::validarColuna(int coluna) { 
    std::vector<int> numerosJaVistos; 
  
    for (int i = 0; i < tamanho; i++) { 
  		int posicao = i*tamanho + coluna;

        //se o numero atual ja foi visto, retorna falso
        if (contem(numerosJaVistos, nodes[posicao].valor)) 
            return false; 

        if (nodes[posicao].valor == 0 || nodes[posicao].valor > tamanho)
            return false;

        numerosJaVistos.push_back(nodes[posicao].valor);

    } 
    return true; 
} 

bool Grafo::validarQuadrante(int linhaInicial, int colunaInicial) { 
    std::vector<int> numerosJaVistos; 
  
    for (int linha = 0; linha < quantidadeLinhas; linha++) { 
        for (int coluna = 0; coluna < quantidadeColunas; coluna++) { 

        	int posicao = (linha + linhaInicial)*tamanho + (coluna + colunaInicial);
  
            //se o numero atual ja foi visto, retorna falso
            if (contem(numerosJaVistos, nodes[posicao].valor)) 
                return false; 

            if (nodes[posicao].valor == 0 || nodes[posicao].valor > tamanho)
	            return false;

	        numerosJaVistos.push_back(nodes[posicao].valor);
  
        } 
    } 
    return true; 
} 
  
bool Grafo::validarPosicao(int linha, int coluna) { 
    return validarLinha(linha) && validarColuna(coluna) && 
           validarQuadrante(linha - linha % quantidadeLinhas, coluna - coluna % quantidadeColunas); 
} 
  
bool Grafo::validarSolucao() { 
    for (int i = 0; i < tamanho; i++) { 
        for (int j = 0; j < tamanho; j++) { 
            if (!validarPosicao(i, j)) 
                return false; 
        } 
    } 
    return true; 
} 

void Grafo::imprimir() {
    for (int linha=0; linha<tamanho; linha++) {
        for (int coluna=0; coluna<tamanho; coluna++) {
            int posicao = linha*tamanho + coluna;
            std::cout << nodes[posicao].valor << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

#endif