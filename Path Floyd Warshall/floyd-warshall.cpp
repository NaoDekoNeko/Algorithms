#include <iostream>
#include <unordered_map>
#include <limits>
#include <string>
#include <vector>

using namespace std;

const int N=4;
const int maxDist = numeric_limits<int>::max(); 

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
        void insertarArista(int,int,int);
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

void Grafo::insertarArista(int verticeA,int verticeB,int peso)
 {
    Nodo * nodoB = new Nodo(verticeB);
    nodoB->peso = peso;
    nodoB->siguiente = lista_nodos[verticeA];
    lista_nodos[verticeA] = nodoB;
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
        cout<<endl;
}

void algFloydWarshall(Grafo g){
	//inicializacion de variables
	int n = g.n_vertices; 
	vector<vector<int>> cam(n,vector<int>(n));
	vector<vector<int>> dist(n,vector<int>(n));
	//inicializacion de matrices cam y dist
	for(int s=0; s<n; s++)
		for (int t=0; t<n; t++){
				cam[s][t]=-1;
				if(s!=t)
					dist[s][t]= maxDist;
				else
					dist[s][t]=0; 
		}
	//asignamos a dist las distancias de los nodos 
	for(int s=0; s<n; s++){
		Nodo* adj = g.lista_nodos[s];
		while(adj !=nullptr){
			dist[s][adj->vertice] = adj->peso;
			adj = adj->siguiente;
		};
	}		
	//asignamos a cam los padres de los nodos
	for(int s=0; s<n; s++)
		for (int t=0; t<n; t++){
			if(dist[s][t]<maxDist)
				cam[s][t]=t; 
		}		
	//inicializacion de algoritmo
	for(int k=0; k<n; k++)
		for(int s=0; s<n; s++)
			for (int t=0; t<n; t++){
				if( dist[s][k] != maxDist && dist[k][t] != maxDist && s!=t ){
					int d = dist[s][k] + dist[k][t];
					if(d < dist[s][t] ){
						cam[s][t]=cam[s][k];
						dist[s][t]=d;
					}	
				}
			}
	//imprimir dist
	cout<<endl;
	cout<<"dist\t";
	for(int i=0; i<n; i++)
		cout<<i<<"\t";
	cout<<endl;
	for(int i=0; i<n; i++){
		cout<<i;
		for (int j=0; j<n; j++){
			if(dist[i][j]==maxDist)
				cout<<"\t"<<"-"; 
			else
				cout<<"\t"<<dist[i][j]; 
		}
			
		cout<<endl;
	}	
	//imprimir cam
	cout<<endl;
	cout<<"cam\t";
	for(int i=0; i<n; i++)
		cout<<i<<"\t";
	cout<<endl;
	for(int i=0; i<n; i++){
		cout<<i;
		for (int j=0; j<n; j++){
			if(cam[i][j]==-1)
				cout<<"\t"<<"-"; 
			else
				cout<<"\t"<<cam[i][j]; 
		}
			
		cout<<endl;
	}	
}

int main(){
	Grafo g = Grafo(N);
	int d;
	g.insertarArista(0,2,4);
	g.insertarArista(1,0,-2);
	g.insertarArista(1,2,3);
	g.insertarArista(2,3,-1);
	g.insertarArista(3,1,2);
	cout<<"Grafo"<<endl;
	g.imprimir();
	cout<<"Algoritmo de Floy Warshall"<<endl;
	algFloydWarshall(g);
	
}
