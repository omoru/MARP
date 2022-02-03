
//Oscar Morujo Fernandez

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

struct Solucion
{
    EntInf coste;
    EntInf potencia;
};

/*

Programacion dinamica ascendente para poder reducir coste en espacio


minCoste(i,j) : minimo coste para conseguir una potencia j teniendo en cuenta los tipos de bombillas de la 1 a la i

Casos base:
    minCoste(_,0) = 0
    minCoste(0,_)= Infinito
Caso recursivo:
    minCoste(i,j) = min(minCoste(i-1,j),minCoste(i,j-pi) + ci)

Al calcularse la tabla habria que recorrer las columnas de Pmin a Pmax para ver cual es la optima y quedarse con el menor de los costes
*/

/*
Espacio: O(maxPotencia) , se calcula la matriz sobre un solo vector, de manera que estando en la posicion j, lo que hay a la izquierda es la
         parte procesada(fila i, es decir, la actual),y en la parte derecha la fila anterior, la i-1
Tiempo: O(numBombillas x maxPotencia)
*/
Solucion resuelve_optima(int minPotencia, int maxPotencia, const vector<int> &potencias, const vector<int> &costes)
{
    int n = potencias.size();
    vector<EntInf> dv(maxPotencia + 1, Infinito);
    dv[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = potencias[i - 1]; j <= maxPotencia; j++)
        {
            dv[j] = min(dv[j], dv[j - potencias[i - 1]] + costes[i - 1]);
        }
    }

    EntInf minCoste = dv[minPotencia];
    EntInf potencia_optima = minPotencia;
    for (int i = minPotencia + 1; i <= maxPotencia; i++)
    {
        if (dv[i] < minCoste)
        {
            minCoste = dv[i];
            potencia_optima = i;
        }
    }
    return {minCoste, potencia_optima};
}

bool resuelveCaso()
{
    int numBombillas, minPotencia, maxPotencia;
    vector<int> potencias(numBombillas), costes(numBombillas);

    cin >> numBombillas;

    if (!std::cin)
        return false;

    cin >> maxPotencia >> minPotencia;

    int coste, potencia;
    for (int i = 0; i < numBombillas; i++)
    {
        cin >> potencia;
        potencias.push_back(potencia);
    }

    for (int i = 0; i < numBombillas; i++)
    {
        cin >> coste;
        costes.push_back(coste);
    }

    Solucion solucion = resuelve_optima(minPotencia, maxPotencia, potencias, costes);

    if (solucion.coste == Infinito)
        cout << "IMPOSIBLE\n";
    else
        cout << solucion.coste << " " << solucion.potencia << '\n';

    return true;
}

int main()
{
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso())
        ;

        // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
