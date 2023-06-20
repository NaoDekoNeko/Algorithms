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
	this->siguiente = nullptr;
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

class Cola{
	public:
		Nodo* delante;
		Nodo* atras;
		Cola();
		bool colaVacia();
		void insertarCola(int);
		int sacarCola();
		void imprimir();
};

Cola::Cola(){
	delante = nullptr;
	atras = nullptr;
}

bool Cola::colaVacia(){
	if(delante==nullptr)
		return true;
	return false;
}

void Cola::insertarCola(int r){
	Nodo* aux = new Nodo(r);
	if(delante == nullptr){
		delante = aux;
	}else{
		atras->siguiente = aux;
	}
	atras = aux;
}

int Cola::sacarCola(){
	int vertice;
	Nodo* aux;
	aux = delante;
	vertice = aux->vertice;
	delante = delante->siguiente;
	delete(aux);
	return vertice;
}

void Cola::imprimir(){
	Nodo* aux;
	aux = delante;
	cout<<"cola\t\t";
	while (aux != nullptr)
    {
        cout<<aux->vertice<<" ";
        aux = aux->siguiente;
    };
    cout<<endl;
}

void algBusqueda(Grafo g);
void BFS(Grafo g,int r);
void imprimir();

Cola c;
int ord[8];
int contador;

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
	c = Cola();
	contador=0;
	for(int i= 0; i<8 ;i++)
	{
		ord[i]=-1;
	}
	BFS(g, 0);
}

void BFS(Grafo g,int r)
{
	c.insertarCola(r);
	while(!c.colaVacia())
	{
		int v = c.sacarCola();
		if(ord[v]==-1)
		{
			ord[v]=contador++;
			Nodo * aux = g.lista_nodos[v];
			while (aux != nullptr)
			{
				int w = aux->vertice;
				if(ord[w]==-1)
				{
					c.insertarCola(w);
				}
			    aux = aux->siguiente;
			};
		}
	}
}

void imprimir()
{
	int n = 8;
	cout<<endl;
	cout<<"nodos\t\t";
	for(int i=0; i<n; i++)
	{
    	cout<<i<<" ";
	}
	cout<<endl;
	cout<<"orden\t\t";
	for(int i=0; i<n; i++)
	{
    	cout<<ord[i]<<" ";
	}
	cout<<endl;
}
