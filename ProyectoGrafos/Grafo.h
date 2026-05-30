

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

    // Ejer 3 y 4
    vector<vector<int>> buildUndirectedAdj() {
        vector<vector<int>> undirected(vertices);
        for (int u = 0; u < vertices; u++) {
            for (auto& e : adjList[u]) {
                int v = e.getDestination();
                undirected[u].push_back(v);
                undirected[v].push_back(u);
            }
        }
        return undirected;
    }

    void ComponentesConexasDebiles() {
        auto adj = buildUndirectedAdj();
        vector<bool> visited(vertices, false);
        int totalComponentes = 0, componenteMayor = 0;

        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                // BFS sobre grafo no dirigido
                queue<int> q;
                q.push(i);
                visited[i] = true;
                int tam = 0;
                while (!q.empty()) {
                    int cur = q.front(); q.pop(); tam++;
                    for (int nb : adj[cur])
                        if (!visited[nb]) { visited[nb] = true; q.push(nb); }
                }
                totalComponentes++;
                if (tam > componenteMayor) componenteMayor = tam;
            }
        }
        cout << "Total de islas: " << totalComponentes << endl;
        cout << "Componente principal: " << componenteMayor << " nodos" << endl;
    }

    double DiametroVial() {
        // Paso 1: Dijkstra desde nodo 0
        vector<double> d1 = dijkstra(0);
        int u = 0;
        double maxD = 0;
        for (int i = 0; i < vertices; i++) {
            if (d1[i] != 999999999 && d1[i] > maxD) {
                maxD = d1[i]; u = i;
            }
        }
        // Paso 2: Dijkstra desde u
        vector<double> d2 = dijkstra(u);
        int v = 0;
        double diametro = 0;
        for (int i = 0; i < vertices; i++) {
            if (d2[i] != 999999999 && d2[i] > diametro) {
                diametro = d2[i]; v = i;
            }
        }
        cout << "Diametro vial aproximado: " << diametro << " metros" << endl;
        cout << "Entre nodos: " << u << " y " << v << endl;
        return diametro;
    }

    double MSTPrim() {
        vector<double> key(vertices, 999999999);
        vector<bool> inMST(vertices, false);
        key[0] = 0;
        double totalDistancia = 0;
        int nodosEnMST = 0;

        Monticulo<pair<double, int>> heap;
        heap.insertar({ 0.0, 0 });

        while (true) {
            pair<double, int> actual;
            if (!heap.eliminar(actual)) break;

            int u = actual.second;
            if (inMST[u]) continue;
            inMST[u] = true;
            totalDistancia += actual.first;
            nodosEnMST++;

            for (auto& e : adjList[u]) {
                int v = e.getDestination();
                double w = e.getWeight();
                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    heap.insertar({ w, v });
                }
            }
        }

        cout << "MST cubre " << nodosEnMST << " nodos" << endl;
        cout << "Distancia total MST: " << totalDistancia / 1000.0 << " km" << endl;
        return totalDistancia;
    }

    double velocidadPorFclass(const string& fclass) {
        if (fclass == "motorway") return 100.0;
        if (fclass == "trunk") return 80.0;
        if (fclass == "primary") return 60.0;
        if (fclass == "secondary") return 50.0;
        if (fclass == "tertiary") return 40.0;
        if (fclass == "residential") return 30.0;
        return 20.0; // default
    }
};