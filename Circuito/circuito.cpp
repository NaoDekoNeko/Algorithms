#include <iostream>
#include "grafoSimple.h"

#define INFINITO 1000
#define N 8
 
//complejidad O[log(V)]

int visitado[N];

bool buscarCircuitoDFS(grafo G, int v, int padre)
{
	visitado[v] = 1;
	nodo* aux = G.lista[v];
	while(aux!=nullptr)
	{
		if(visitado[aux->vertice]==-1)
			if(buscarCircuitoDFS(G, aux->vertice, v))
				return true;
		else if(padre!=aux->vertice)
			return true;
		aux = aux->sgte;
	}
	return false;
}

bool existeCircuito(grafo G, int w, int v)
{
	for(int i=0;i<G.n_vertices;i++)
		visitado[i] = -1;
	for(int i=0;i<G.n_vertices;i++)
		if(visitado[i]==-1)
			if(buscarCircuitoDFS(G, v, v))
				return true;
	return false;
}


int main(int argc, char** argv) 
{	
	grafo G = grafo(N);
    G.insertarArista(0,1,3);
    G.insertarArista(0,2,1);
    G.insertarArista(1,3,1); 
	G.insertarArista(1,6,5);  
    G.insertarArista(2,3,2);
    G.insertarArista(2,5,5);
    G.insertarArista(3,4,4);
    G.insertarArista(3,5,2);
    G.insertarArista(4,7,1);
    G.insertarArista(4,6,2);
    G.imprimir();
    
    if(existeCircuito(G,0,0))
    	std::cout<<"Existe circuito\n";
    else
    	std::cout<<"No existe circuito\n";
    
	return 0;
}
