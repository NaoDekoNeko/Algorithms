#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

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

    Nodo * obtenerNodo(int v){
        Nodo * aux = nodos;
        while(aux){
            if(aux->id == v)
                return aux;
            aux = aux ->sgte;
        }
        return nullptr;
    }

    int getPeso(int u, int v){
        Nodo * aux1 = obtenerNodo(u);
        Arista * aux = aux1->aristas;
        while(aux){
            if(aux->destino == v)
                return aux->peso;
            aux = aux->sgte;
        }
        return INT_MAX;
    }
};

void printPath(std::vector<int> prev, int source, int destination) {
    //como no debe tener ciclos, no se imprime el camino de un nodo a él mismo, además su distancia es 0
    if(source == destination) return;
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

std::pair<std::vector<int>,std::vector<int>> bellmanFord(Grafo * grafo, int origen) {
    int n = grafo->vertices();
    
    //primero se crean los vectores distancia y predecesor
    std::vector<int> distancia(n,INT_MAX);
    std::vector<int> predecesor(n,-1);
    //al iniciar, la distancia al origen es 0
    //y se pone como predecesor del origen al mismo origen
    distancia[origen] = 0;
    predecesor[origen] = origen;

    //durante |V|-1 iteraciones:
    for (int i = 1; i <= n - 1; i++) {
        //para cada nodo
        for (Nodo * nodo = grafo->nodos; nodo != nullptr; nodo = nodo->sgte) {
            //sus adyacentes
            for (Arista * arista = nodo->aristas; arista != nullptr; arista = arista->sgte) {
                int u = nodo->id;
                int v = arista->destino;
                int peso = arista->peso;
                //mientras la distancia que se recorre no sea infinita y se cumpla que sea mínima
                if (distancia[u] != INT_MAX && distancia[u] + peso < distancia[v]) {
                    distancia[v] = distancia[u] + peso;
                    predecesor[v] = u;
                }
            }
        }
    }

    //analiza si tiene ciclos de peso negativo
    for (Nodo * nodo = grafo->nodos; nodo != nullptr; nodo = nodo->sgte) {
        for (Arista * arista = nodo->aristas; arista != nullptr; arista = arista->sgte) {
            int u = nodo->id;
            int v = arista->destino;
            int peso = arista->peso;
            if (distancia[u] != INT_MAX && distancia[u] + peso < distancia[v]) {
                std::cerr << "El grafo contiene un ciclo de peso negativo" << std::endl;
                exit(1);
            }
        }
    }

    return std::make_pair(distancia,predecesor);
}

void showBellmanFord(Grafo * grafo, int origen){
    int n = grafo->vertices();
    auto res = bellmanFord(grafo,origen);
    auto distancia = res.first;
    auto predecesor = res.second;

    std::cout << "\nDistancias finales desde el vertice " <<char('A'+origen)<<" hasta cada vértice:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << char('A' + i) << ": " << distancia[i] << std::endl;
    }

    Grafo spt(n);
    
    for(int i=0;i<n;i++){
        if(i == origen) continue;
        if(predecesor[i]!=-1){
            int peso = grafo->getPeso(predecesor[i],i);
            spt.insertarArista(predecesor[i],i,peso);
        }
    }
    
    spt.imprimir();

    std::cout<<std::endl;

    for(int i=0;i<grafo->vertices();i++){

        printPath(predecesor,origen,i);

        std::cout<<std::endl;

    }
}

int main(){
    //Grafo Tarea
    Grafo grafo(6);
    grafo.insertarArista(0, 1, 41);
    grafo.insertarArista(0, 5, 29);
    grafo.insertarArista(1, 2, 51);
    grafo.insertarArista(1, 4, 32);
    grafo.insertarArista(2, 3, 50);
    grafo.insertarArista(3, 0, 15);
    grafo.insertarArista(3, 5, -38);
    grafo.insertarArista(4, 3, 36);
    grafo.insertarArista(4, 2, 32);
    grafo.insertarArista(5, 1, -29);
    grafo.insertarArista(5, 4, 21);
    grafo.imprimir();
    for(int i=0;i<grafo.vertices();i++){
        std::cout << std::endl;
        showBellmanFord(&grafo,i);
    }
    //Grafo que viene después de tarea
    Grafo ejem(7);
    ejem.insertarArista(0,1,6);
    ejem.insertarArista(0,2,5);
    ejem.insertarArista(0,3,5);
    ejem.insertarArista(1,4,-1);
    ejem.insertarArista(2,1,-2);
    ejem.insertarArista(2,4,1);
    ejem.insertarArista(3,2,-2);
    ejem.insertarArista(3,5,-1);
    ejem.insertarArista(4,6,3);
    ejem.insertarArista(5,6,3);
    ejem.imprimir();
    for(int i=0;i<ejem.vertices();i++){
        std::cout << std::endl;
        showBellmanFord(&ejem,i);
    }
    
    return 0;
}