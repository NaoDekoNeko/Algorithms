#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

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
    
    //inserta aristas no dirigidas
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

void printPath(std::vector<int> prev, int source, int destination) {
    // Crear un vector para almacenar el camino
    std::vector<int> path;
    // Inicializar el nodo actual con el nodo de destino
    int current = destination;
    // Mientras el nodo actual no sea el nodo de origen
    while (current != source) {
        // Si el predecesor del nodo actual es -1, entonces no hay camino
        if (prev[current] == -1) {
            std::cout << "No hay camino de " << char('A' + source) << " hacia " << char('A' + destination) << std::endl;
            return;
        }
        // Agregar el nodo actual al camino
        path.push_back(current);
        // Actualizar el nodo actual con su predecesor
        current = prev[current];
    }
    // Agregar el nodo de origen al camino
    path.push_back(source);
    // Invertir el orden del camino
    std::reverse(path.begin(), path.end());
    // Imprimir el camino
    std::cout << "Camino de " << char('A' + source) << " hacia " << char('A' + destination) << std::endl;
    for (int i = 0; i < path.size(); i++) {
        std::cout << char('A' + path[i]);
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
}

std::pair<std::vector<int>, std::vector<int>> dijkstra(Grafo *grafo, int fuente) {
    // Inicializar el vector de distancias con valores infinitos
    int n = 0;
    for (Nodo * nodo = grafo->nodos; nodo != nullptr; nodo = nodo->sgte) {
        n++;
    }
    std::vector<int> dist(n, std::numeric_limits<int>::max());
    dist[fuente] = 0;
    
    // Inicializar el vector de predecesores
    std::vector<int> prev(n, -1);
    
    // Crear una cola de prioridad para almacenar los nodos a visitar
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, fuente));
    
    // Mientras la cola de prioridad no esté vacía
    int step = 1;
    while (!pq.empty()) {
        // Obtener el siguiente nodo a visitar
        int u = pq.top().second;
        pq.pop();
        
        // Buscar el nodo u en la lista de nodos
        Nodo * nodoU = grafo->nodos;
        while (nodoU != nullptr && nodoU->id != u) {
            nodoU = nodoU->sgte;
        }
        
        // Para cada arista del nodo u
        if (nodoU != nullptr) {
            for (Arista * arista = nodoU->aristas; arista != nullptr; arista = arista->sgte) {
                int v = arista->destino;
                int peso = arista->peso;
                
                // Si se encuentra un camino más corto al nodo v
                if (dist[v] > dist[u] + peso) {
                    // Actualizar la distancia al nodo v
                    dist[v] = dist[u] + peso;
                    // Actualizar el predecesor del nodo v
                    prev[v] = u;
                    // Agregar el nodo v a la cola de prioridad
                    pq.push(std::make_pair(dist[v], v));
                    
                    // Imprimir el camino y la distancia al nodo v
                    std::cout << "Paso " << step << ": ";
                    for (int i = 0; i < n; i++) {
                        if (dist[i] != std::numeric_limits<int>::max()) {
                            std::cout << char('A' + i);
                            if (i < n - 1) {
                                std::cout << ",";
                            }
                        }
                    }
                    std::cout << " distancia: " << dist[v] << std::endl;
                    step++;
                }
            }
        }
    }
    
    // Devolver el vector de distancias y el vector de predecesores
    return std::make_pair(dist, prev);
}

void ShowDijkstra(Grafo * grafo, int fuente){
    std::cout << "Grafo:\n";
    grafo->imprimir();
    std::cout << std::endl;
    // Correr el algoritmo de dijkstra
    auto result = dijkstra(grafo, 0);
    std::vector<int> dist = result.first;
    std::vector<int> prev = result.second;

    // Crea el grafo que representa el SPT
    Grafo spt(dist.size());

    std::cout <<"\nAlgoritmo de Dijkstra:\n";
    // Añade las aristas
    for (int v = 0; v < dist.size(); v++) {
        if (prev[v] != -1) {
            int u = prev[v];
            int peso = dist[v] - dist[u];
            spt.insertarArista(u, v, peso);
        }
    }
    std::cout<<"\nArbol SPT:\n";
    // imprime el SPT
    spt.imprimir();
    std::cout<<std::endl;
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

    ShowDijkstra(&grafo,0);
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

    ShowDijkstra(&G,0);
*/
    Grafo aux = Grafo(5);
    aux.insertarArista(0,1,10);
    aux.insertarArista(0,4,100);
    aux.insertarArista(1,2,50);
    aux.insertarArista(2,4,10);
    aux.insertarArista(0,3,30);
    aux.insertarArista(3,4,60);
    aux.insertarArista(3,2,20);

    ShowDijkstra(&aux,0);

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


    ShowDijkstra(&profe,0);

    return 0;
}