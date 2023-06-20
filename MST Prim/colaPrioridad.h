#ifndef COLAPRIORIDAD_H
#define COLAPRIORIDAD_H

#include <iostream>
#include "grafoSimple.h"

struct cola
{
private:
    void encolar(int, int);
    void ordenar();
public:
    nodo* delante;
    nodo* atras;
    cola();
    bool estaVacia();
    bool buscar(int);
    void insertar(int, int);
    nodo* eliminar();
    void actualizar(int, int);
    void imprimir();
};

cola::cola()
{
    delante = nullptr;
    atras = nullptr;
}

bool cola::estaVacia()
{
    return (delante == nullptr);
}

void cola::encolar(int vertice, int peso)
{
    nodo* aux = new nodo(vertice);
    aux->peso = peso;
    aux->sgte = nullptr;
    if (delante == nullptr)
        delante = aux;
    else
        atras->sgte = aux;
    atras = aux;
}

void cola::ordenar()
{
    nodo* aux1;
    nodo* aux2;
    aux1 = delante;
    while (aux1->sgte != nullptr)
    {
        aux2 = aux1->sgte;
        while (aux2 != nullptr)
        {
            if (aux1->peso > aux2->peso)
            {
                int dtemp = aux1->vertice;
                int ptemp = aux1->peso;
                aux1->vertice = aux2->vertice;
                aux1->peso = aux2->peso;
                aux2->vertice = dtemp;
                aux2->peso = ptemp;
            }
            aux2 = aux2->sgte;
        }
        aux1 = aux1->sgte;
    }
}

bool cola::buscar(int item)
{
    nodo* aux;
    aux = delante;
    while (aux != nullptr)
    {
        if (aux->vertice == item)
            return true;
        aux = aux->sgte;
    }
    return false;
}

void cola::insertar(int vertice, int peso)
{
    encolar(vertice, peso);
    ordenar();
}

nodo* cola::eliminar()
{
    nodo* aux;
    aux = delante;
    delante = delante->sgte;
    if (aux->sgte != nullptr)
        ordenar();
    return aux;
}

void cola::actualizar(int v, int p)
{
    nodo* aux;
    aux = delante;
    while (aux != nullptr)
    {
        if (aux->vertice == v)
            aux->peso = p;
        aux = aux->sgte;
    }
}

void cola::imprimir()
{
    nodo* aux;
    aux = delante;
    std::cout << "Cola de Prioridad: ";
    while (aux != nullptr)
    {
        std::cout << aux->vertice << " ";
        aux = aux->sgte;
    }
    std::cout << "\n";
}

#endif  // COLAPRIORIDAD_H
