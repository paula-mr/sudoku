#ifndef UTIL_CPP
#define UTIL_CPP

#include "Util.h"

int encontrarMaiorValor(std::vector<int> vetor) {
	int max = vetor[0];
	for (unsigned int i=1; i < vetor.size(); i++) {
		if (vetor[i] > max) {
			max = vetor[i];
		}
	}

	return max;
}

bool contem(std::vector<int> vetor, int elemento) {
    return (std::find(vetor.begin(), vetor.end(), elemento) != vetor.end());
}

#endif