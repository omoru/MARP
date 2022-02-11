

// Oscar Morujo Fernandez

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "EnterosInf.h"
#include <algorithm>
#include "Matriz.h"

using namespace std;

/*

floyd(k,i,j) : minima distancia para ir del vertice i al vertice j, pudiendo usar como intermedios los vertices del 1 al k

N-> numPersonas
Casos base:
    floyd(0,i,j) = G[i][j] con 0 <= j,i < N 
    floyd(k,i,i) = 0 con 0<=i <N
Caso recursivo:
    floyd(k,i,j) = min(floyd(k-1,i,j),floyd(k-1,i,k) + floyd(k-1,k,j))

Llamada inicial:
    floyd(k=N)

Espacio: O(N^2)
Tiempo: O(N^3)
*/

void floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C) {
    int V = G.numfils(); // número de vértices de G
    // inicialización
    C = G; // C0
    // actualizaciones de las matrices: de arriba a abajo y de izq a dcha ya que la fila y columna k no cambian respecto a Ck-1
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                EntInf temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) { // es mejor pasar por k
                    C[i][j] = temp;
                }
            }
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
    int numPersonas, numRelaciones;
    cin >> numPersonas;

    if (!std::cin)
        return false;

    cin >> numRelaciones;

    string persona1, persona2;
    // CONSTRUCCION GRAFO
    Matriz<EntInf> G(numPersonas, numPersonas, Infinito);
    unordered_map<string, int> diccionario;
    int id = 0;
    int id1, id2;
    for (int i = 0; i < numRelaciones; i++)
    {
        cin >> persona1 >> persona2;

        if (diccionario.find(persona1) == diccionario.cend())
        {
            diccionario.insert({persona1, id});
            id1 = id;
            id++;
        }
        else
            id1 = diccionario.at(persona1);
        if (diccionario.find(persona2) == diccionario.cend())
        {
            diccionario.insert({persona2, id});
            id2 = id;
            id++;
        }
        else
            id2 = diccionario.at(persona2);

        G[id1][id2] = 1;
        G[id2][id1] = 1;
    }

    for (int i = 0; i < numPersonas; i++)
        G[i][i] = 0;

    //---------------------------

    //Resolvemos el problema
    Matriz<EntInf> C(numPersonas, numPersonas, Infinito);
    floyd(G, C);

    //recorremos la matriz Ck por filas de arriba a abajo( solo el triangulo superior ya que es simetrico y nos quedamos con el maximo)
    EntInf max = C[0][0];
    for (int i = 0; i < numPersonas; i++)
    {
        for (int j = i; j < numPersonas; j++)
        {
            if (C[i][j] > max)
                max = C[i][j];
        }
    }
    if (max == Infinito)
        cout << "DESCONECTADA\n";
    else
        cout << max << '\n';

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
