#include "Grafo.h"

void Alcanze_Vehicular(Grafo& const ) {

}


int main() {

    Grafo g(886790, true);

    g.cargarCSV("edges.csv");

    cout << "Carga completa\n";

    cout << g.getAdjList()[0].size();
    g.printGraph();
    return 0;
}