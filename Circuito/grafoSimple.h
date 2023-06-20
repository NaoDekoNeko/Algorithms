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
    void insertarArista(int , int , int );
    void imprimir();
};

grafo::grafo(int n)
{
	this->n_vertices = n;
	for(int i=0; i<n; i++)
		lista.insert({i, nullptr});
};

void grafo::insertarArista(int verticeA, int verticeB, int peso){
    nodo * auxB = new nodo(verticeB);
	auxB->peso = peso;
	auxB->sgte = lista[verticeA];
	lista[verticeA] = auxB;
	nodo * auxA = new nodo(verticeA);
	auxA->peso = peso;
	auxA->sgte = lista[verticeB];
	lista[verticeB] = auxA;
};
		
void grafo::imprimir(){
    for(int i =0; i<n_vertices;i++)
    {
	    nodo * aux = lista[i];
	    std::cout<<"Vertices Adyacentes de nodo "<<i<<":";
	    while (aux != nullptr)
	    {
	        std::cout<<" -> " << aux->vertice;
	        aux = aux->sgte;
	    }
	    std::cout<<"\n";    
    }
};
