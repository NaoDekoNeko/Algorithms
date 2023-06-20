#include <iostream>
#include <vector>
#include <map>
#include <climits>

using namespace std;

// Función para encontrar el costo mínimo de visitar todos los nodos
int TSP(vector<vector<int>> &grafo, map<pair<int, int>, pair<int, int>> &lookup, int pos, int visitados) {
    int N = grafo.size();

    // Si todos los nodos han sido visitados
    if (visitados == ((1 << N) - 1)) {
        return grafo[pos][0]; // Regresar al nodo inicial
    }

    // Crear una clave para el mapa
    pair<int, int> clave = make_pair(pos, visitados);

    // Si el subproblema ya fue resuelto
    if (lookup.count(clave)) {
        return lookup[clave].first;
    }

    // Inicializar el costo mínimo con un valor alto
    int minimo = INT_MAX;
    int siguiente = -1;

    // Recorrer todos los nodos
    for (int k = 0; k < N; k++) {
        // Si el nodo no ha sido visitado
        if (!(visitados & (1 << k))) {
            // Calcular el costo mínimo de visitar el nodo k
            int costo = grafo[pos][k] + TSP(grafo, lookup, k, visitados | (1 << k));

            // Actualizar el costo mínimo y el siguiente nodo a visitar
            if (costo < minimo) {
                minimo = costo;
                siguiente = k;
            }
        }
    }

    // Guardar la solución en el mapa
    lookup[clave] = make_pair(minimo, siguiente);

    // Retornar el costo mínimo
    return minimo;
}

// Función para imprimir el camino óptimo
void printPath(vector<vector<int>> &grafo, map<pair<int, int>, pair<int, int>> &lookup, int pos, int visitados, int contador) {
    cout << pos;

    // Si se ha visitado más de una vez el nodo inicial
    if (pos == 0 && contador > 1) {
        cout << endl;
        return;
    }

    cout << " -> ";

    // Obtener el siguiente nodo en el camino óptimo
    pair<int, int> clave = make_pair(pos, visitados);
    int siguiente = lookup[clave].second;

    if (siguiente != -1) {
        printPath(grafo, lookup, siguiente, visitados | (1 << siguiente), contador + (siguiente == 0));
    } else {
        cout << 0 << endl;
    }
}

int main() {
    //ejemplo 1
    vector<vector<int>> grafo{{0,1,15,6},{2,0,7,3},{9,6,0,12},{10,4,8,0}};
    
    cout << "\t";
    
    for(int i = 0; i < grafo.size(); i++)
        cout << i << "\t";
    cout << endl;

    for(int i = 0; i < grafo.size(); i++)
    {   
        cout << i << "\t";
        for(int j = 0; j< grafo.size();j++)
            cout << grafo[i][j] << "\t";
        cout << endl;
    }

    

    //ejemplo 2
    /*
    vector<vector<int>> grafo{
        {0, 10, 15, 20, 25, 30},
        {10, 0, 35, 25, 30, 15},
        {15, 35, 0, 30, 5, 20},
        {20, 25, 30, 0, 15, 35},
        {25, 30, 5, 15, 0, 20},
        {30, 15, 20, 35, 20, 0}
    };
    */

    // Crear un mapa para guardar las soluciones a los subproblemas
    map<pair<int, int>, pair<int, int>> lookup;

    // Calcular el costo mínimo de visitar todos los nodos
    cout << "El costo mínimo es " << TSP(grafo, lookup, 0, 1) << endl;

    // Imprimir el camino óptimo
    cout << "El camino óptimo es: ";
    printPath(grafo, lookup, 0, 1, 1);

    return 0;
}