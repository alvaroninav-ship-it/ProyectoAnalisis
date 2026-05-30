

#include "Edge.h"
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include "Monticulo.h"
class Grafo {
private:

    vector<vector<Edge>> adjList;

    int vertices;

    bool isDirected;

public:

    Grafo(int v, bool directed = false) {

        vertices = v;

        isDirected = directed;

        adjList.resize(vertices);
    }

    // =====================================
    // AGREGAR ARISTA
    // =====================================
    void addEdge(int u, int v, double weight) {

        adjList[u].push_back(Edge(v, weight));

        if (!isDirected) {

            adjList[v].push_back(Edge(u, weight));
        }
    }

    // =====================================
    // IMPRIMIR GRAFO
    // =====================================
    void printGraph() {

        for (int i = 0; i < vertices; i++) {

            cout << i << " -> ";

            for (auto& e : adjList[i]) {

                cout << "("
                    << e.getDestination()
                    << ", "
                    << e.getWeight()
                    << ") ";
            }

            cout << endl;
        }
    }
    int Contar() {
        int cont = 0;
        for (int i = 0; i < vertices; i++) {
            for (auto& e : adjList[i]) {
                cont++;
            }
        }
        return cont;
    }

    // =====================================
    // BFS
    // =====================================
    int BFS(int start,
        vector<bool>& visited) {

        queue<int> q;

        q.push(start);

        visited[start] = true;

        int tamano = 0;

        while (!q.empty()) {

            int current = q.front();

            q.pop();

            tamano++;

            for (auto& neighbor :
                adjList[current]) {

                int next =
                    neighbor.getDestination();

                if (!visited[next]) {

                    visited[next] = true;

                    q.push(next);
                }
            }
        }

        return tamano;
    }
    // =====================================
    // ISLAS VIALES
    // =====================================



    void ComponentesConexas() {

        vector<bool> visited(vertices, false);

        int totalComponentes = 0;

        int componenteMayor = 0;

        for (int i = 0; i < vertices; i++) {

            if (!visited[i]) {

                int tamano =
                    BFS(i, visited);

                totalComponentes++;


                if (tamano > componenteMayor) {

                    componenteMayor = tamano;
                }
            }
        }

        cout << "Total de islas: " << endl;
        cout<< totalComponentes<< endl;

        cout << "Componente principal: "
            << componenteMayor
            << " nodos"<<endl;
    }

    // =====================================
    // DIJKSTRA
    // =====================================
   
    vector<double> dijkstra(int start) {

        vector<double> dist(vertices, 999999999);

        Monticulo<pair<double, int>> heap;
        dist[start] = 0;

        heap.insertar({ 0, start });

        while (true) {

            pair<double, int> actual;

            if (!heap.eliminar(actual))
                break;

            double distanciaActual =
                actual.first;

            int nodoActual =
                actual.second;

            for (auto& vecino :
                adjList[nodoActual]) {

                int siguiente =
                    vecino.getDestination();

                double peso =
                    vecino.getWeight();

                double nuevaDistancia =
                    distanciaActual + peso;

                if (nuevaDistancia <
                    dist[siguiente]) {

                    dist[siguiente] =
                        nuevaDistancia;

                    heap.insertar({
                        nuevaDistancia,
                        siguiente
                        });
                }
            }
        }

        return dist;
    }

    // =====================================
    // ALCANCE VEHICULAR
    // =====================================
    int AlcanceVehicular(
        int origen,
        double maxDistance = 5000.0
    ) {

        vector<double> dist =
            dijkstra(origen);

        int alcanzables = 0;

        for (double d : dist) {

            if (d <= maxDistance) {

                alcanzables++;
            }
        }

        return alcanzables;
    }

    // =====================================
    // CARGAR CSV
    // =====================================
    void cargarCSV(string filename) {

        ifstream file(filename);

        if (!file.is_open()) {

            cout << "Error abriendo archivo\n";

            return;
        }

        string line;

        getline(file, line);

        while (getline(file, line)) {

            stringstream ss(line);

            string osm_id;
            string from;
            string to;
            string distance;
            string fclass;
            string oneway;
            string maxspeed;

            getline(ss, osm_id, ',');
            getline(ss, from, ',');
            getline(ss, to, ',');
            getline(ss, distance, ',');
            getline(ss, fclass, ',');
            getline(ss, oneway, ',');
            getline(ss, maxspeed, ',');

            if (from.empty() ||
                to.empty() ||
                distance.empty()) {
                continue;
            }

            int u = stoi(from);

            int v = stoi(to);

            double w = stod(distance);

            addEdge(u, v, w);
        }

        file.close();

        cout << "Grafo cargado correctamente"<<endl;
    }

    // =====================================
    // GETTERS
    // =====================================
    int getVertices() {
        return vertices;
    }

    vector<vector<Edge>>& getAdjList() {
        return adjList;
    }
};