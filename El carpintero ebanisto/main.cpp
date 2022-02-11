// Oscar Morujo Fernandez

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"

using namespace std;

const int INFINITO = 1000000000;
/*

Similar al de multiplicacion encadenada de matrices

minEsfuerzo(i,j) : minimo esfuerzo necesario para realizar los cortes del i al j.

N -> numero de cortes

Casos base:
    minEsfuerzo(i,i)  = 0
Caso recursivo:
    minEsfuerzo(i,j) =  for i< k< j : min { minEsfuerzo(i,k) + 2*(cortes[j]-cortes[i])+  minEsfuerzo(k,j)}

Llamada inicial:
    minEsfuerzo(1,N)

Espacio: O(N^2)
Tiempo: O(N^3)
*/

// Version ascendente del algoritmo : se recorre por filas la matriz  de izquierda a derecha y de arriba a abajo
int minEsfuerzo(const vector<int> &cortes)
{
    int n = cortes.size(); // -> n+2, el del 0 y el de la longitud
    Matriz<int> mat(n, n, 0);
    // Los  casos bases estan en la diagonal principal (=0)
    // Realizamos recorrido por diagonales ya que los elementos que necesitamos estan en las diagonales anteriores
    for (int d = 2; d < n; d++)
    {
        for (int i = 0; i < n - d; i++) // recorremos los elementos de la diagonal
        {
            int j = i + d; // j -> columna
            int minimo = INFINITO;
            for (int k = i + 1; k < j; k++)
            {
                minimo = min(minimo, mat[i][k] + mat[k][j] + 2 * (cortes[j] - cortes[i]));
            }
            mat[i][j] = minimo;
        }
    }
    return mat[0][n - 1];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    int longitud, numCortes, tamCorte;
    vector<int> cortes;
    cin >> longitud >> numCortes;

    if (longitud == 0 && numCortes == 0)
        return false;

    // Añadimos los cortes en 0 y en longitud -> numCortes+2 elementos
    cortes.push_back(0);
    for (int i = 0; i < numCortes; i++)
    {
        cin >> tamCorte;
        cortes.push_back(tamCorte);
    }
    cortes.push_back(longitud);

    cout << minEsfuerzo(cortes) << '\n';

    return true;
}

int main()
{
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso())
        ;

        // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    // system("PAUSE");
#endif
    return 0;
}
