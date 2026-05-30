#include "Grafo.h"

int main() {
    Grafo g(886790, true);

    g.cargarCSV("edges.csv");

    cout << "Carga completa" << endl;
    cout << "Total aristas: " << g.Contar() << endl;

    // Alcance Vehicular
    int alcanzables = g.AlcanceVehicular(0);
    cout << "Nodos alcanzables en 5km desde nodo 0: "
        << alcanzables << endl;

    // Islas Viales
    g.ComponentesConexas();

    // Diametro Vial
    g.DiametroVial();

    return 0;
}