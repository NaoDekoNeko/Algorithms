#include "colaPrioridad.h"
#include <chrono>
#define N 8
#define INFINITO 1000 

int cPeso(int v, int w, grafo G)
{
    nodo* aux = G.lista[v];
    int peso = -1; // Cambiado para asignar un valor inicial que indique que no se encontró la arista
    while (aux != nullptr)
    {
        if (aux->vertice == w)
        {
            peso = aux->peso;
            break;
        }
        aux = aux->sgte;
    }
    return peso;
}

void algPrim(grafo G)
{
    int distancia[N];
    int padre[N];
    bool visitado[N]; // Nuevo arreglo para marcar los nodos visitados

    for (int i = 0; i < N; i++)
    {
        distancia[i] = INFINITO;
        padre[i] = -1;
        visitado[i] = false; // Inicializar todos los nodos como no visitados
    }

    distancia[0] = 0;
    //va a visitar N-1 nodos
    for (int i = 0; i < N - 1; i++)
    {
        int minDistancia = INFINITO;
        int minNodo = -1;

        for (int j = 0; j < N; j++)
        {
            if (!visitado[j] && distancia[j] < minDistancia)
            {
                minDistancia = distancia[j];
                minNodo = j;
            }
        }

        if (minNodo == -1)
            break;

        visitado[minNodo] = true;

        nodo* aux = G.lista[minNodo];
        while (aux != nullptr)
        {
            int peso = cPeso(minNodo, aux->vertice, G);

            if (!visitado[aux->vertice] && peso != -1 && distancia[aux->vertice] > peso)
            {
                padre[aux->vertice] = minNodo;
                distancia[aux->vertice] = peso;
            }
            aux = aux->sgte;
        }
    }

    std::cout << "\npadre\t";
    for (int i = 0; i < N; i++)
        std::cout << padre[i] << " ";

    std::cout << "\nnodos\t";
    for (int i = 0; i < N; i++)
        std::cout << i << " ";

    std::cout << "\ndist\t";
    for (int i = 0; i < N; i++)
        std::cout << distancia[i] << " ";

    std::cout << "\n\nMST Prim\n\n";
    grafo res = grafo(N);
    for (int i = 1; i < N; i++)
        res.insertarArista(padre[i], i, distancia[i]);
    res.imprimir();
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    /*
    grafo g = grafo(9);
    g.insertarArista(0, 1, 4);
    g.insertarArista(0, 7, 8);
    g.insertarArista(1, 2, 8);
    g.insertarArista(1, 7, 11);
    g.insertarArista(2, 3, 7);
    g.insertarArista(2, 8, 2);
    g.insertarArista(2, 5, 4);
    g.insertarArista(3, 4, 9);
    g.insertarArista(3, 5, 14);
    g.insertarArista(4, 5, 10);
    g.insertarArista(5, 6, 2);
    g.insertarArista(6, 7, 1);
    g.insertarArista(6, 8, 6);
    g.insertarArista(7, 8, 7);
    g.imprimir();
	algPrim(g);
    */
   /*
    grafo G(12);
    G.insertarArista(0, 1, 4);
    G.insertarArista(0, 2, 1);
    G.insertarArista(1, 2, 2);
    G.insertarArista(1, 3, 7);
    G.insertarArista(1, 4, 3);
    G.insertarArista(2, 3, 5);
    G.insertarArista(2, 5, 6);
    G.insertarArista(3, 4, 2);
    G.insertarArista(3, 5, 1);
    G.insertarArista(4, 5, 4);
    G.insertarArista(4, 6, 6);
    G.insertarArista(4, 7, 3);
    G.insertarArista(5, 7, 8);
    G.insertarArista(5, 8, 5);
    G.insertarArista(6, 7, 1);
    G.insertarArista(6, 9, 7);
    G.insertarArista(7, 8, 2);
    G.insertarArista(8, 10, 3);
    G.insertarArista(9, 11, 4);
    G.imprimir();
    algPrim(G);
    */
    grafo g(8);
    g.insertarArista(0,6,53);
    g.insertarArista(0,1,32); 
    g.insertarArista(0,2,29);
    g.insertarArista(4,3,34);
    g.insertarArista(5,3,18);
    g.insertarArista(7,4,46);
    g.insertarArista(5,4,40);
    g.insertarArista(0,5,60); 
    g.insertarArista(6,4,51);
    g.insertarArista(7,0,31);
    g.insertarArista(7,6,25);
    g.insertarArista(7,1,21);
    g.imprimir();
    algPrim(g);

    // Obtiene el tiempo de finalización
    auto end = std::chrono::high_resolution_clock::now();

    // Calcula la duración de la ejecución
    std::chrono::duration<double> duration = end - start;

    // Imprime el tiempo de ejecución en segundos
    std::cout << "Tiempo de ejecución: " << duration.count() << " segundos" << std::endl;

	return 0;
}


