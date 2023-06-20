#include <iostream>
#include <queue>
#include <vector>
#include <limits>

// Estructura para representar una arista con un nodo destino y un peso
struct Arista {
    int destino;
    int peso;
    Arista(int destino, int peso) : destino(destino), peso(peso) {}
};

// Estructura para representar un nodo con un identificador y una lista de aristas
struct Nodo {
    int id;
    std::vector<Arista> aristas;
    Nodo(int id) : id(id) {}
};

// Estructura para representar un grafo con una lista de nodos y una función para agregar aristas
struct Grafo {
    std::vector<Nodo> nodos;
    Grafo(int n) {
        for (int i = 0; i < n; i++) {
            nodos.push_back(Nodo(i));
        }
    }
    void insertarArista(int desde, int hasta, int peso) {
        nodos[desde].aristas.push_back(Arista(hasta, peso));
    }
    
    // Función para imprimir el grafo en el formato especificado
    void imprimir() {
        for (int i = 0; i < nodos.size(); i++) {
            std::cout << "Vertices Adyacentes de nodo " << char('A' + i) << ": ";
            for (Arista arista : nodos[i].aristas) {
                std::cout << " -> " << char('A' + arista.destino) << " (" << arista.peso << ")";
            }
            std::cout << std::endl;
        }
    }
};

std::pair<std::vector<int>, std::vector<int>> dijkstra(Grafo *grafo, int fuente) {
    // Inicializar el vector de distancias con valores infinitos
    std::vector<int> dist(grafo->nodos.size(), std::numeric_limits<int>::max());
    dist[fuente] = 0;
    
    // Inicializar el vector de predecesores
    std::vector<int> prev(grafo->nodos.size(), -1);
    
    // Crear una cola de prioridad para almacenar los nodos a visitar
    std::priority_queue<std::pair<int, int>, //tipo de dato (nodos)
    std::vector<std::pair<int, int>>, //tipo de contenedor (vector que almacena nodos)
    std::greater<std::pair<int, int>>> pq; //función de comparación ascendente
    pq.push(std::make_pair(0, fuente));  //añade el primer nodo tanto como vertice como fuente
    
    // Mientras la cola de prioridad no esté vacía
    int step = 1;
    while (!pq.empty()) {
        // Obtener el siguiente nodo a visitar
        int u = pq.top().second;
        pq.pop();
        
        // Para cada arista del nodo u
        for (Arista arista : grafo->nodos[u].aristas) {
            int v = arista.destino;
            int peso = arista.peso;
            
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
                for (int i = 0; i < grafo->nodos.size(); i++) {
                    if (dist[i] != std::numeric_limits<int>::max()) {
                        std::cout << char('A' + i);
                        if (i < grafo->nodos.size() - 1) {
                            std::cout << ",";
                        }
                    }
                }
                std::cout << " distancia: " << dist[v] << std::endl;
                step++;
            }
        }
    }
    
    // Devolver el vector de distancias y el vector de predecesores
    return std::make_pair(dist, prev);
}

void ShowDijkstra(Grafo * grafo, int fuente){
    grafo->imprimir();
    // Correr el algoritmo de dijkstra
    auto result = dijkstra(grafo, 0);
    std::vector<int> dist = result.first;
    std::vector<int> prev = result.second;

    // Crea el grafo que representa el SPT
    Grafo spt(grafo->nodos.size());

    // Añade las aristas
    for (int v = 0; v < grafo->nodos.size(); v++) {
        if (prev[v] != -1) {
            int u = prev[v];
            int peso = dist[v] - dist[u];
            spt.insertarArista(u, v, peso);
        }
    }

    // imprime el SPT
    spt.imprimir();
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

    std::cout << std::endl;
    
    Grafo profe = Grafo(6);
    profe.insertarArista(0,1,41);
    profe.insertarArista(1,0,41);
    profe.insertarArista(1,2,51);
    profe.insertarArista(2,1,51);
    profe.insertarArista(2,3,50);
    profe.insertarArista(3,2,50);
    profe.insertarArista(3,4,36);
    profe.insertarArista(4,3,36);
    profe.insertarArista(3,5,38);
    profe.insertarArista(5,3,38);
    profe.insertarArista(3,0,45);
    profe.insertarArista(0,3,45);
    profe.insertarArista(5,0,29);
    profe.insertarArista(0,5,29);
    profe.insertarArista(4,5,21);
    profe.insertarArista(5,4,21);
    profe.insertarArista(1,4,32);
    profe.insertarArista(4,1,32);
    profe.insertarArista(4,2,32);
    profe.insertarArista(2,4,32);
    profe.insertarArista(5,1,24);
    profe.insertarArista(1,5,24);

    ShowDijkstra(&profe,0);
    return 0;
}