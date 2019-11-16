#ifndef NODE_H
#define NODE_H

#include <vector>

class Node {

    public:
        std::vector<int> adjacencias;
        std::vector<int> valoresRemovidos;
        int valor;
};

#endif