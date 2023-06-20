#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <chrono>

struct nodo
{
    int vertice;
    int peso;
    nodo* sgte;
    nodo(int v) : vertice(v), peso(0), sgte(nullptr) {}
};

struct grafo
{
    int n_vertices;
    std::unordered_map<int, nodo*> lista;
    grafo(int n) : n_vertices(n) {
        for (int i = 0; i < n; i++)
            lista.insert({ i, nullptr });
    }
    void insertarArista(int v1, int v2, int peso) {
        nodo* auxV2 = new nodo(v2);
        auxV2->peso = peso;
        auxV2->sgte = lista[v1];
        lista[v1] = auxV2;

        nodo* auxV1 = new nodo(v1);
        auxV1->peso = peso;
        auxV1->sgte = lista[v2];
        lista[v2] = auxV1;
    }
    void imprimir() {
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
};

struct arista {
    int v1;
    int v2;
    int peso;
    arista(int _v1, int _v2, int _peso) : v1(_v1), v2(_v2), peso(_peso) {}
};

bool compararAristas(const arista& a1, const arista& a2) {
    return a1.peso < a2.peso;
}

struct encontrarUnion {
    std::vector<int> padre;
    std::vector<int> rango;

    encontrarUnion(int n) {
        padre.resize(n);
        rango.resize(n, 0);
        for (int i = 0; i < n; i++)
            padre[i] = i;
    }
    //encuentra al padre del vertice v
    int encontrar(int v) {
        if (padre[v] != v)
            padre[v] = encontrar(padre[v]);
        return padre[v];
    }
    
    void unir(int v1, int v2) {
        int raizV1 = encontrar(v1);
        int raizV2 = encontrar(v2);
        //si tiene padres diferentes 
        if (raizV1 != raizV2) {
            //si el rango de raizV1 es menor, raizV se asigna como padre de raizV1
            if (rango[raizV1] < rango[raizV2])
                padre[raizV1] = raizV2;
            //si ocurre al revés, el padre de raizV2 se vuelve raizV1
            else if (rango[raizV1] > rango[raizV2])
                padre[raizV2] = raizV1;
            //si ambos tienen el mismo rango
            //el padre de raizV2 se vuelve raizV1 y se aumenta el rango de raizV1 en 1
            else {
                padre[raizV2] = raizV1;
                rango[raizV1]++;
            }
        }
    }
};

void kruskal(grafo& G) {
    std::vector<arista> aristas;
    //para cada vertice
    for (auto& par : G.lista) {
        int v1 = par.first;
        nodo* auxiliar = par.second;
        //minetras el nodo al que apunta no sea null
        while (auxiliar != nullptr) {
            int v2 = auxiliar->vertice;
            int peso = auxiliar->peso;
            //si el nodo actual es menor que su adyacente
            if (v1 < v2)
                aristas.push_back(arista(v1, v2, peso)); //se agrega esa arista al vector aristas
            auxiliar = auxiliar->sgte;
        }
    }

    //se va a ordenar todos los elementos del vector aristas segpun el peso de las mismas
    std::sort(aristas.begin(), aristas.end(), compararAristas);

    encontrarUnion uf(G.n_vertices);
    //se crea un vector que almacenará las aristas del MST
    std::vector<arista> arbolExpansionMinima;

    for (const auto& arista : aristas) {
        //valores auxiliares para la arista
        int v1 = arista.v1;
        int v2 = arista.v2;
        int peso = arista.peso;
        //busca los padres de los vertices
        int raizV1 = uf.encontrar(v1);
        int raizV2 = uf.encontrar(v2);
        //si tienen padres diferentes
        if (raizV1 != raizV2) {
            //se unen los vertices
            uf.unir(raizV1, raizV2);
            //se añade la arista al MST
            arbolExpansionMinima.push_back(arista);
        }
    }

    std::cout << "Arbol de Expansion Minima (Kruskal):\n";
    for (const auto& arista : arbolExpansionMinima) {
        std::cout << arista.v1 << " - " << arista.v2 << " (" << arista.peso << ")\n";
    }

    // Imprimir el MST utilizando el método imprimir de la estructura grafo
    grafo MST(G.n_vertices);
    for (const auto& arista : arbolExpansionMinima) {
        MST.insertarArista(arista.v1, arista.v2, arista.peso);
    }
    std::cout << "Arbol de Expansion Minima (MST):\n";
    MST.imprimir();
}


int main() {
    auto start = std::chrono::high_resolution_clock::now();
    /*
    grafo G(8);
    G.insertarArista(0, 2, 4);
    G.insertarArista(0, 1, 2);
    G.insertarArista(1, 6, 1);
    G.insertarArista(1, 3, 5);
    G.insertarArista(2, 5, 6);
    G.insertarArista(2, 3, 1);
    G.insertarArista(3, 5, 2);
    G.insertarArista(3, 4, 10);
    G.insertarArista(4, 6, 3);
    G.insertarArista(4, 7, 2);
    G.insertarArista(5, 2, 6);
    G.insertarArista(5, 3, 2);
    G.insertarArista(6, 1, 1);
    G.insertarArista(6, 4, 3);
    G.insertarArista(7, 4, 2);
    G.imprimir();
    kruskal(G);
    */
    /*
    grafo g = grafo(10);
   	g.insertarArista(0, 1, 1);
    g.insertarArista(0, 2, 1);
    g.insertarArista(1, 2, 1);
    g.insertarArista(1, 3, 1);
    g.insertarArista(2, 4, 1);
    g.insertarArista(3, 4, 1);
    g.insertarArista(3, 5, 1);
    g.insertarArista(4, 6, 1);
    g.insertarArista(5, 6, 1);
    g.insertarArista(6, 7, 1);
    g.insertarArista(6, 8, 1);
    g.insertarArista(7, 8, 1);
    g.insertarArista(7, 9, 1);
    g.insertarArista(8, 9, 1);
    g.insertarArista(0, 4, 1);
    g.insertarArista(1, 4, 1);
    g.insertarArista(3, 6, 1);
	g.imprimir();
    kruskal(g);
    */
    /*
    grafo G = grafo(10);
   	G.insertarArista(0, 1, 1);
    G.insertarArista(0, 2, 1);
    G.insertarArista(0, 4, 1);
    G.insertarArista(1, 3, 1);
    G.insertarArista(1, 4, 1);
    G.insertarArista(1, 0, 1);
    G.insertarArista(2, 0, 1);
    G.insertarArista(3, 5, 1);
    G.insertarArista(3, 6, 1);
    G.insertarArista(3, 1, 1);
    G.insertarArista(4, 0, 1);
    G.insertarArista(4, 6, 1);
    G.insertarArista(4, 3, 1);
    G.insertarArista(4, 2, 1);
    G.insertarArista(5, 3, 1);
    G.insertarArista(5, 6, 1);
    G.insertarArista(6, 7, 1);
    G.insertarArista(6, 8, 1);
    G.insertarArista(6, 3, 1);
    G.insertarArista(6, 4, 1);
    G.insertarArista(7, 9, 1);
    G.insertarArista(7, 6, 1);
    G.insertarArista(8, 6, 1);
    G.insertarArista(9, 7, 1);
	G.imprimir();
    kruskal(G);
    */
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
    kruskal(g);
    */
   /*
    grafo G = grafo(12);
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
    kruskal(G);
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
    kruskal(g);

    // Obtiene el tiempo de finalización
    auto end = std::chrono::high_resolution_clock::now();

    // Calcula la duración de la ejecución
    std::chrono::duration<double> duration = end - start;

    // Imprime el tiempo de ejecución en segundos
    std::cout << "Tiempo de ejecución: " << duration.count() << " segundos" << std::endl;

    return 0;
}
