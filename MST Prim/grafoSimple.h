#ifndef GRAFOSIMPLE_H
#define GRAFOSIMPLE_H

#include <iostream>
#include <unordered_map>

struct nodo
{
    int vertice;
    int peso;
    nodo* sgte;
    nodo(int);
};

nodo::nodo(int vertice)
{
    this->vertice = vertice;
}

struct grafo
{
    int n_vertices;
    std::unordered_map<int, nodo*> lista;
    grafo(int);
    void insertarArista(int, int, int);
    void imprimir();
};

grafo::grafo(int n)
{
    this->n_vertices = n;
    for (int i = 0; i < n; i++)
        lista.insert({ i, nullptr });
};

void grafo::insertarArista(int verticeA, int verticeB, int peso)
{
    // Verificar si el vértice de destino ya está presente en la lista de adyacencia del vértice de origen
    nodo* aux = lista[verticeA];
    while (aux != nullptr) {
        if (aux->vertice == verticeB) {
            // El vértice de destino ya está presente, no es necesario agregar un nuevo nodo
            return;
        }
        aux = aux->sgte;
    }

    // Agregar un nuevo nodo al inicio de la lista de adyacencia del vértice de origen
    nodo* nuevoNodo = new nodo(verticeB);
    nuevoNodo->peso = peso;
    nuevoNodo->sgte = lista[verticeA];
    lista[verticeA] = nuevoNodo;

    // Agregar un nuevo nodo al inicio de la lista de adyacencia del vértice de destino (en la dirección opuesta)
    nodo* nuevoNodoOpuesto = new nodo(verticeA);
    nuevoNodoOpuesto->peso = peso;
    nuevoNodoOpuesto->sgte = lista[verticeB];
    lista[verticeB] = nuevoNodoOpuesto;
}

void grafo::imprimir()
{
    for (int i = 0; i < n_vertices; i++) {
        nodo* aux = lista[i];
        std::cout << "Vertices Adyacentes de nodo " << i << ":";
        while (aux != nullptr) {
            std::cout << " -> " << aux->vertice << " (" << aux->peso << ")";
            aux = aux->sgte;
        }
        std::cout << "\n";
    }
}

#endif  // GRAFOSIMPLE_H
