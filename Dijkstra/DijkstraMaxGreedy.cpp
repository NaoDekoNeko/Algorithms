#include <iostream>
#include <tuple>

using namespace std;

class Edge{
public:
    int weight;
    int destiny;
    Edge * next;

    Edge(int weight, int destiny){
        this->weight = weight;
        this->destiny = destiny;
        this->next = nullptr;
    }
};

class Vertex{
public:
    int data;
    Vertex * next;
    Edge * edges;

    Vertex(int data){
        this->data = data;
        this->next = nullptr;
        this->edges = nullptr;
    }

    void addVertex(int data){
        Vertex * newVertex = new Vertex(data);
        Vertex * vertex = this;
        while(vertex->next != nullptr){
            vertex = vertex->next;
        }
        vertex->next = newVertex;
        
    }
};

class Graph{
    int size = 1;
    Vertex * Vertices;
public:

    Graph(){
        this->Vertices = nullptr;
    }

    void addVertex(){
        Vertex * newVertex = new Vertex(size);
        if(this->Vertices == nullptr){
            this->Vertices = newVertex;
        }else{
            Vertex * vertex = this->Vertices;
            while(vertex->next != nullptr){
                vertex = vertex->next;
            }
            vertex->next = newVertex;
        }
        size++;
    }

    void addEdge(int src, int to, int weight){
        if(!this->Vertices){
            return;
        }
        
        Vertex * vertex = findVertex(src);

        if(vertex != nullptr){
            Edge * newEdge = new Edge(weight, to);
            newEdge->next = vertex->edges;
            vertex->edges = newEdge;
        }
    }

    void addNDEdge(int src, int to, int weight){
        addEdge(src, to, weight);
        addEdge(to, src, weight);
    }

    void printGraph(){
        Vertex * vertex = this->Vertices;

        while(vertex != nullptr){
            cout << char(vertex->data + 'A') << " -> ";
            Edge * edge = vertex->edges;

            while(edge != nullptr){
                cout << char(edge->destiny + 'A') << " ";
                edge = edge->next;
            }

            cout << endl;
            vertex = vertex->next;
        }
    }

    tuple<int*,int*,bool*> DijkstraMaxGreed(int, int);
    Vertex * findVertex(int);
};

tuple<int*,int*,bool*> Graph::DijkstraMaxGreed(int src, int to)
{
    bool * visit = new bool[this->size];
    int * dist = new int[this->size];
    int * prev = new int[this->size];

    int answer = -1;

    for(int i = 0; i < this->size; i++){
        visit[i] = false;
        dist[i] = -1;
        prev[i] = -1;
    }

    prev[src] = src;
    dist[src] = 0;

    Vertex * vertex = findVertex(src);
    Vertex * max;

    while(vertex != findVertex(to)){
        Edge * edge = vertex->edges;

        while(edge != nullptr){
            if(visit[edge->destiny]){
                edge = edge->next;
                continue;
            }

            int d = dist[vertex->data] + edge->weight;

            if(edge->destiny == to){
                if(d > answer){
                    answer = d;
                    prev[to] = vertex->data;
                }
            }
            else{
                if(d > dist[edge->destiny]){
                    dist[edge->destiny] = d;
                    prev[edge->destiny] = vertex->data;
                }
            }

            edge = edge->next;
        }

        visit[vertex->data] = true;

        // Find the next vertex with maximum distance
        max = nullptr;
        int maxDist = -1;
        for (int i=0; i<this->size; i++) {
            if (!visit[i] && dist[i] > maxDist) {
                maxDist = dist[i];
                max = findVertex(i);
            }
        }

        // If no more vertices can be reached, break
        if (max == nullptr) {
            break;
        }

        vertex = max;
    }

    cout << "Max distance: " << answer << endl;

    return make_tuple(dist, prev, visit);
}

Vertex *Graph::findVertex(int data)
{
    if(!this->Vertices){
        return nullptr;
    }

    Vertex * vertex = this->Vertices;

    while(vertex != nullptr){
        if(vertex->data == data){
            return vertex;
        }
        vertex = vertex->next;
    }

    return nullptr;
}

/*
Dijkstra algorithm with a greedy approach
*/
int main(){
    Graph * graph = new Graph();
    graph->addVertex();
    graph->addVertex();
    graph->addVertex();
    graph->addVertex();
    graph->addVertex();

    graph->addNDEdge(1, 2, 2);
    graph->addNDEdge(1, 4, 3);
    graph->addNDEdge(1, 5, 6);
    graph->addNDEdge(2, 4, 3);
    graph->addNDEdge(2, 3, 4);
    graph->addNDEdge(3, 4, 1);
    graph->addNDEdge(3, 5, 3);
    graph->addNDEdge(4, 5, 3);

    graph->printGraph();

    cout << endl;

    auto result = graph->DijkstraMaxGreed(1, 2);

    auto mst = make_tuple(get<0>(result), get<1>(result));

    return 0;
}




