#include "Grafo.h"



int main() {

    Grafo g(886790, true);

    g.cargarCSV("edges.csv");

    cout << "Carga completa\n";

    cout << g.Contar() << endl;
    int grafos_Alcanzables = g.AlcanceVehicular(0);
    cout << "Numero de grafos alcanzables en el rango de 5000 km: " << grafos_Alcanzables << endl;
    g.ComponentesConexas();
    return 0;
}