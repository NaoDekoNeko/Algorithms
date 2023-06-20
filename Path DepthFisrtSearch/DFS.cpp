#include <iostream>
#include <unordered_map>

using namespace std;

class Nodo
{
    public:
	    int vertice;
	    int peso;
	    Nodo* siguiente;
    	Nodo(int);
};

Nodo::Nodo(int vertice)
{
	this->vertice = vertice;
}

class Grafo
{
    public:
        int n_vertices;
        unordered_map<int,Nodo*> lista_nodos;  
        Grafo(int);
        void agregar_aristas(int,int,int);
        void imprimir();
};

Grafo::Grafo(int n)
{   
    this->n_vertices = n;
    for(int i=0;i<n;i++)
    {
        lista_nodos.insert({i,nullptr});
    };
}

void Grafo::agregar_aristas(int verticeA,int verticeB,int peso)
 {
    Nodo * nodoB = new Nodo(verticeB);
    nodoB->peso = peso;
    nodoB->siguiente = lista_nodos[verticeA];
    lista_nodos[verticeA] = nodoB;
    Nodo * nodoA = new Nodo(verticeA);
    nodoA->peso = peso;
    nodoA->siguiente = lista_nodos[verticeB];
    lista_nodos[verticeB] = nodoA;
}

void Grafo::imprimir()
{
        for(int i =0; i<n_vertices;i++)
        {
            string adyacentes = "Vertices Adyacentes de ["+ to_string(i)+"]:";
            Nodo * aux = lista_nodos[i];
            while (aux != nullptr)
            {
                adyacentes += " -> "+ to_string(aux->vertice);
                aux = aux->siguiente;
            };
            cout<<adyacentes<<endl;
        };
}

void algBusqueda(Grafo g);
void DFS(Grafo g, int v);
void imprimir();

int cont;
int pre[8];


int main()
{
  
    Grafo g = Grafo(8);
    g.agregar_aristas(0,7,0);
    g.agregar_aristas(0,5,0);
    g.agregar_aristas(0,2,0);  
    g.agregar_aristas(2,6,0);
    g.agregar_aristas(7,1,0);
    g.agregar_aristas(5,3,0);
    g.agregar_aristas(5,4,0);
    g.agregar_aristas(3,4,0);
    g.imprimir();
    
    algBusqueda(g);
    imprimir();
    
    return 0;
}

void algBusqueda(Grafo g)
{
	cont=0;
	for(int v=0; v < g.n_vertices;v++)
	{
		pre[v]=-1;
	}
	for(int v=0; v < g.n_vertices;v++)
	{
		if (pre[v]==-1)
		{
			DFS(g,v);
		}
	}
}

void DFS(Grafo g, int v)
{
	pre[v]=cont++;
	Nodo * aux = g.lista_nodos[v];
	while (aux != nullptr)
        {
            int w = aux->vertice;
            if(pre[w]==-1)
			{
            	DFS(g,w);
			}
            aux = aux->siguiente;
        };
}

void imprimir()
{
	int n = 8;
	cout<<endl;
	cout<<"nodos\t\t";
	for(int i=0; i<n; i++){
    	cout<<i<<" ";
	}
	cout<<endl;
	cout<<"preorden\t";
	for(int i=0; i<n; i++){
    	cout<<pre[i]<<" ";
	}
	cout<<endl;
}
