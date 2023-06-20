#include <iostream>
#include <queue>
#include <vector>
#include <limits>

// Estructura para representar una arista con un nodo destino y un peso
struct Arista {
    int destino;
    int peso;
    Arista * sgte;
    Arista(int destino, int peso) : destino(destino), peso(peso), sgte(nullptr) {}
};

// Estructura para representar un nodo con un identificador y una lista de aristas
struct Nodo {
    int id;
    Arista * aristas;
    Nodo * sgte;
    Nodo(int id) : id(id), aristas(nullptr), sgte(nullptr){}
};

// Estructura para representar un grafo con una lista de nodos y una función para agregar aristas
struct Grafo {
    Nodo * nodos;
    Grafo(int n) : nodos(nullptr) {
        for (int i = n - 1; i >= 0; i--) {
            Nodo * nuevoNodo = new Nodo(i);
            nuevoNodo->sgte = nodos;
            nodos = nuevoNodo;
        }
    }
    
    int vertices(){
        int n = 0;
        for (Nodo * nodo = nodos; nodo != nullptr; nodo = nodo->sgte) {
            n++;
        }
        return n;
    }

    void insertarArista(int desde, int hasta, int peso) {
        Nodo * nodo = nodos;
        while (nodo != nullptr && nodo->id != desde) {
            nodo = nodo->sgte;
        }
        if (nodo != nullptr) {
            Arista * nuevaArista = new Arista(hasta, peso);
            nuevaArista->sgte = nodo->aristas;
            nodo->aristas = nuevaArista;
        }
    }

    void insertarAristaND(int desde, int hasta, int peso) {
        insertarArista(desde,hasta,peso);
        insertarArista(hasta,desde,peso);
    }
    
    // Función para imprimir el grafo en el formato especificado
    void imprimir() {
        for (Nodo * nodo = nodos; nodo != nullptr; nodo = nodo->sgte) {
            std::cout << "Vertices Adyacentes de nodo " << char('A' + nodo->id) << ": ";
            for (Arista * arista = nodo->aristas; arista != nullptr; arista = arista->sgte) {
                std::cout << " -> " << char('A' + arista->destino) << " (" << arista->peso << ")";
            }
            std::cout << std::endl;
        }
    }
};


//firma alternativa
//std::vector<std::vector<int>> floydWarshall(Grafo *grafo) {
void floydWarshall(Grafo *grafo){
    // Inicializar el vector de distancias con valores infinitos
    int n = grafo->vertices();
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, std::numeric_limits<int>::max()));
    
    // Inicializar las distancias entre cada par de nodos
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    for (Nodo * nodo = grafo->nodos; nodo != nullptr; nodo = nodo->sgte) {
        for (Arista * arista = nodo->aristas; arista != nullptr; arista = arista->sgte) {
            int u = nodo->id;
            int v = arista->destino;
            int peso = arista->peso;
            dist[u][v] = peso;
        }
    }
    
    // Imprimir la matriz de distancias inicial
    std::cout << "\nMatriz de distancias inicial:" << std::endl;
    for(int i = 0; i<=n;i++)
            if(i==0)
                std::cout << "Distancias";
            else
                std::cout <<"\t"<< char('A'+i-1)<<"\t";
        std::cout<<std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << char('A'+i)<<"\t|\t";
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == std::numeric_limits<int>::max()) {
                std::cout << "inf\t|\t";
            } else {
                std::cout << dist[i][j] << "\t|\t";
            }
        }
        std::cout << std::endl;
    }
    
    // Ejecutar el algoritmo de Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != std::numeric_limits<int>::max() && dist[k][j] != std::numeric_limits<int>::max()) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        
        // Imprimir la matriz de distancias en el paso k
        std::cout << "\nMatriz de distancias en el paso " << k + 1 << ":" << std::endl;
        for(int i = 0; i<=n;i++)
            if(i==0)
                std::cout << "Distancias";
            else
                std::cout <<"\t"<< char('A'+i-1)<<"\t";
        std::cout<<std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << char('A'+i)<<"\t|\t";
            for (int j = 0; j < n; j++) {
                if (dist[i][j] == std::numeric_limits<int>::max()) {
                    std::cout << "inf\t|\t";
                } else {
                    std::cout << dist[i][j] << "\t|\t";
                }
            }
            std::cout << std::endl;
        }
    }
    
    // Devolver el vector de distancias/parte de la firma alternativa
    //return dist;
}


int main() {
    
    // Crear un grafo con 8 nodos
    Grafo grafo(8);
    
    // Agregar algunas aristas al grafo
    grafo.insertarArista(0,6,53);
    grafo.insertarArista(0,1,32); 
    grafo.insertarArista(0,2,29);
    grafo.insertarArista(4,3,34);
    grafo.insertarArista(5,3,18);
    grafo.insertarArista(7,4,46);
    grafo.insertarArista(5,4,40);
    grafo.insertarArista(0,5,60); 
    grafo.insertarArista(6,4,51);
    grafo.insertarArista(7,0,31);
    grafo.insertarArista(7,6,25);
    grafo.insertarArista(7,1,21);
    grafo.imprimir();
    floydWarshall(&grafo);
    /*
    Grafo G = Grafo(12);
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
    floydWarshall(&G);
*/
    Grafo aux = Grafo(5);
    aux.insertarArista(0,1,10);
    aux.insertarArista(0,4,100);
    aux.insertarArista(1,2,50);
    aux.insertarArista(2,4,10);
    aux.insertarArista(0,3,30);
    aux.insertarArista(3,4,60);
    aux.insertarArista(3,2,20);
    aux.imprimir();
    floydWarshall(&aux);
    

    Grafo profe = Grafo(6);
    profe.insertarAristaND(0,1,41);
    profe.insertarAristaND(1,2,51);
    profe.insertarAristaND(2,3,50);
    profe.insertarAristaND(3,4,36);
    profe.insertarAristaND(3,5,38);
    profe.insertarAristaND(3,0,45);
    profe.insertarAristaND(5,0,29);
    profe.insertarAristaND(4,5,21);
    profe.insertarAristaND(1,4,32);
    profe.insertarAristaND(4,2,32);
    profe.insertarAristaND(5,1,24);

    floydWarshall(&profe);
    
    return 0;
}