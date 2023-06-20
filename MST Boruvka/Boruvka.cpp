#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
/*
    C++ Program
    Boruvka's algorithm for minimum spanning trees
*/
class Arista
{
    public:
    // Arista peso o costo
    int peso;
    int destino;
    int origen;
    Arista *sgte;

    Arista(int peso, int origen, int destino)
    {
        this->peso = peso;
        this->destino = destino;
        this->origen = origen;
        this->sgte = NULL;
    }
};
//esta clase nos dice quién es el padre de un vertice además de su rango (el numero de vertices adyacentes)
class Estado
{
    public: int padre;
    int rango;
    Estado(int padre, int rango)
    {
        this->padre = padre;
        this->rango = rango;
    }
};
class Grafo
{
    public: int vertices;
    vector < vector < Arista *> > graphArista;
    Grafo(int vertices)
    {
        this->vertices = vertices;
       
        for (int i = 0; i < this->vertices; ++i)
        {
            this->graphArista.push_back(vector < Arista *> ());
        }
    }
    void insertarArista(int origen, int destino, int w)
    {
        if (destino < 0 || destino >= this->vertices || 
             origen < 0 || origen >= this->vertices)
        {
            return;
        }
        // inserta nodo de arista
        this->graphArista.at(origen).push_back(new Arista(w, origen, destino));
        if (destino == origen)
        {
            return;
        }
        this->graphArista.at(destino).push_back(new Arista(w, destino, origen));
    }
    void imprimirGrafo()
    {
        cout << "\nLista de Adyacencia del Grafo\n";
        for (int i = 0; i < this->vertices; ++i)
        {
            cout << "Vertices Adyacentes de nodo " << i << ": ";
            // itera sobre Aristas del nodo i
            for (int j = 0; j < this->graphArista.at(i).size(); ++j)
            {
                cout << " -> " << this->graphArista.at(i).at(j)->destino << " (" << this->graphArista.at(i).at(j)->peso << ")";
            }
            cout << endl;
        }
    }
    //busca al padre de un vertice i, lo asigna a su lugar en la matriz y devuelve el padre
    int encontrar(Estado **subsets, int i)
    {
        if (subsets[i]->padre != i)
        {
            subsets[i]->padre = this->encontrar(subsets, subsets[i]->padre);
        }
        return subsets[i]->padre;
    }
    void findUnion(Estado **subsets, int x, int y)
    {
        //se busca los padres de los vertices
        int a = this->encontrar(subsets, x);
        int b = this->encontrar(subsets, y);
        //si el vertice a tiene menos adyacentes que b
        if (subsets[a]->rango < subsets[b]->rango)
        {
            //se asigna como padre de a al vertice b
            subsets[a]->padre = b;
        }
        //si lo contrario ocurre
        else if (subsets[a]->rango > subsets[b]->rango)
        {
            //se asigna como padre de b al vertice a
            subsets[b]->padre = a;
        }
        //si ambos tienen el mismo numero de adyacentes
        else
        {
            //se asigna como padre de b al vertice a y se añade uno al rango de a
            subsets[b]->padre = a;
            subsets[a]->rango++;
        }
    }
    
    void imprimirMST(Arista** mst, int n)
    {
        cout << "\nArbol de Expansion Minima (Minimum Spanning Tree):\n";
        for (int i = 0; i < n; ++i)
        {
            if (mst[i] != NULL)
            {
                cout << "Vertices Adyacentes de nodo " << mst[i]->origen << ":";
                cout << " -> " << mst[i]->destino << " (" << mst[i]->peso << ")";
                cout << endl;

                // También imprimimos la arista en la dirección opuesta
                cout << "Vertices Adyacentes de nodo " << mst[i]->destino << ":";
                cout << " -> " << mst[i]->origen << " (" << mst[i]->peso << ")";
                cout << endl;
            }
        }
    }


    void boruvkaMST()
    {
        // contiene la suma de pesos del MST
        int result = 0;
        int selector = this->vertices;
        //matriz de estado de los vertices
        Estado **subsets = new Estado*[this->vertices];
        //matriz que contendrá el peso de las aristas
        Arista **cheapest = new Arista*[this->vertices];
        //se inicia la matriz con todos los pesos en 0
        for (int v = 0; v < this->vertices; ++v)
        {
            subsets[v] = new Estado(v, 0);
        }
        while (selector > 1)
        {
            //inicia todas las aristas del vertice en null
            for (int v = 0; v < this->vertices; ++v)
            {
                cheapest[v] = NULL;
            }
            //para cada vertice
            for (int k = 0; k < this->vertices; k++)
            {
                //hasta el numero de adyacentes que tenga
                for (int i = 0; i < this->graphArista.at(k).size(); ++i)
                {
                    //se buscará a los padres de los vertices origen y destino
                    int set1 = this->encontrar(subsets, this->graphArista.at(k).at(i)->origen);
                    int set2 = this->encontrar(subsets, this->graphArista.at(k).at(i)->destino);
                    //si sus padres son distintos
                    if (set1 != set2)
                    {
                        //si aún no hay arista de menor costo, se asigna la actual
                        if (cheapest[k] == NULL)
                        {
                            cheapest[k] = this->graphArista.at(k).at(i);
                        }
                        //si el peso de la actual arista de menor peso es mayor que la arista actual
                        //se asigna la arista actual como la de menor peso
                        else if (cheapest[k]->peso > this->graphArista.at(k).at(i)->peso)
                        {
                            cheapest[k] = this->graphArista.at(k).at(i);
                        }
                    }
                }
            }
            //para todos los vertices
            for (int i = 0; i < this->vertices; i++)
            {
                //si su arista menor no está vacía
                if (cheapest[i] != NULL)
                {
                    //se buscará a los padres de los vertices origen y destino
                    int set1 = this->encontrar(subsets, cheapest[i]->origen);
                    int set2 = this->encontrar(subsets, cheapest[i]->destino);
                    //si sus padres son distintos
                    if (set1 != set2)
                    {
                        // Quita una Arista
                        selector--;
                        //busca la union de los vertices en el MST
                        this->findUnion(subsets, set1, set2);
                        // Muestra las conexiones de la arista
                        cout << "\nInsertar Arista (" << cheapest[i]->origen << " - " << cheapest[i]->destino << ") peso " << cheapest[i]->peso;
                        // Añade peso
                        result += cheapest[i]->peso;
                    }
                }
            }
        }
        cout << "\nEl peso total del MST es: " << result << endl;
    
        // Obtener las aristas del MST
        Arista** mst = new Arista*[this->vertices];
        for (int i = 0; i < this->vertices; ++i)
        {
            mst[i] = NULL;
        }
        for (int i = 0; i < this->vertices; ++i)
        {
            if (cheapest[i] != NULL)
            {
                mst[i] = cheapest[i];
            }
        }
    
        // Imprimir el MST
        imprimirMST(mst, this->vertices);
    
        // Liberar memoria
        delete[] mst;
    }
};

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    /*
    Grafo * G = new Grafo(10);
    G->insertarArista(0, 1, 1);
    G->insertarArista(0, 2, 1);
    G->insertarArista(0, 4, 1);
    G->insertarArista(1, 3, 1);
    G->insertarArista(1, 4, 1);
    G->insertarArista(1, 0, 1);
    G->insertarArista(2, 0, 1);
    G->insertarArista(3, 5, 1);
    G->insertarArista(3, 6, 1);
    G->insertarArista(3, 1, 1);
    G->insertarArista(4, 0, 1);
    G->insertarArista(4, 6, 1);
    G->insertarArista(4, 3, 1);
    G->insertarArista(4, 2, 1);
    G->insertarArista(5, 3, 1);
    G->insertarArista(5, 6, 1);
    G->insertarArista(6, 7, 1);
    G->insertarArista(6, 8, 1);
    G->insertarArista(6, 3, 1);
    G->insertarArista(6, 4, 1);
    G->insertarArista(7, 9, 1);
    G->insertarArista(7, 6, 1);
    G->insertarArista(8, 6, 1);
    G->insertarArista(9, 7, 1);
    G->imprimirGrafo();
    G->boruvkaMST();
    */
   /*
    Grafo g = Grafo(9);
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
    g.imprimirGrafo();
    g.boruvkaMST();
    */
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
    G.imprimirGrafo();
    G.boruvkaMST();
    */
    Grafo g(8);
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
    g.imprimirGrafo();
    g.boruvkaMST();

    // Obtiene el tiempo de finalización
    auto end = std::chrono::high_resolution_clock::now();

    // Calcula la duración de la ejecución
    std::chrono::duration<double> duration = end - start;

    // Imprime el tiempo de ejecución en segundos
    std::cout << "Tiempo de ejecución: " << duration.count() << " segundos" << std::endl;

    return 0;
}