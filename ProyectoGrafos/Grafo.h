

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

    // =====================================
    // BFS
    // =====================================
    vector<int> BFS(int start) {

        vector<int> visited(vertices, 0);

        vector<int> order;

        queue<int> q;

        visited[start] = 1;

        q.push(start);

        while (!q.empty()) {

            int current = q.front();

            q.pop();

            order.push_back(current);

            for (auto& neighbor : adjList[current]) {

                int next = neighbor.getDestination();

                if (!visited[next]) {

                    visited[next] = 1;

                    q.push(next);
                }
            }
        }

        return order;
    }

    // =====================================
    // DIJKSTRA
    // =====================================
    vector<double> dijkstra(int start) {

        // Distancias
        vector<double> dist(vertices, 999999999);

        // Min Heap
        priority_queue<
            pair<double, int>,
            vector<pair<double, int>>,
            greater<pair<double, int>>
        > cola;

        // Nodo inicial
        dist[start] = 0;

        cola.push({ 0, start });

        while (!cola.empty()) {

            // Sacar nodo más cercano
            double distanciaActual =
                cola.top().first;

            int nodoActual =
                cola.top().second;

            cola.pop();

            // Recorrer vecinos
            for (auto& vecino : adjList[nodoActual]) {

                int siguiente =
                    vecino.getDestination();

                double peso =
                    vecino.getWeight();

                double nuevaDistancia =
                    distanciaActual + peso;

                // Si mejora
                if (nuevaDistancia < dist[siguiente]) {

                    dist[siguiente] =
                        nuevaDistancia;

                    cola.push({
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

        cout << "Grafo cargado correctamente\n";
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