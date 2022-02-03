

//Oscar Morujo Fernandez

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

/*

Programacion dinamica ascendente para poder reducir coste en espacio

maxPuntuacion(i,j) : maxima puntuacion posible para llegar a la casilla i,j del tablero desde la fila 0

N -> numero de filas/columnas

Casos base:
    maxPuntuacion(0,j) = tablero(0,j) 0<=j< N
Caso recursivo:
    maxPuntuacion(i,j) = max(maxPuntuacion(i-1,j),maxPuntuacion(i-1,j-1),maxPuntuacion(i-1,j+1)) +tablero[i][j]
*/

struct Solucion
{
    int columna;
    int puntuacion;
};

/*
Espacio: O(N) + O(1) del la variable auxiliar
Tiempo: O(NxN)

*/
Solucion maxPuntuacion_optima(int N, const Matriz<int> &tablero)
{

    vector<int> mat(N, 0);
    for (int i = 0; i < N; i++)
        mat[i] = tablero[0][i];

    for (int i = 1; i < N; i++)
    {
        int mat_j, mat_j_mas_1 = 0;
        for (int j = N - 1; j >= 0; j--)
        {
            //mat[j] antes de ser modificado, ya que sera el mat[j+1] en la proxima iteracion
            mat_j = mat[j];
            if (j > 0 && j < N - 1)
                mat[j] = max(max(mat[j], mat[j - 1]), mat_j_mas_1) + tablero[i][j];
            else if (j > 0)
                mat[j] = max(mat[j], mat[j - 1]) + tablero[i][j];
            else
                mat[j] = max(mat[j], mat_j_mas_1) + tablero[i][j];
            mat_j_mas_1 = mat_j;
        }
    }
    int max = 0;
    int pos = 0;
    for (int j = 0; j < N; j++)
    {
        if (mat[j] > max)
        {
            max = mat[j];
            pos = j + 1;
        }
    }

    return {pos, max};
}
/*
Espacio: O(NxN)
Tiempo: O(NxN)

*/
Solucion maxPuntuacion(int N, const Matriz<int> &tablero)
{
    Matriz<int> mat(N, N, 0);
    for (int i = 0; i < N; i++)
        mat[0][i] = tablero[0][i];
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j > 0 && j < N - 1)
                mat[i][j] = max(max(mat[i - 1][j], mat[i - 1][j - 1]), mat[i - 1][j + 1]) + tablero[i][j];
            else if (j > 0)
                mat[i][j] = max(mat[i - 1][j], mat[i - 1][j - 1]) + tablero[i][j];
            else
                mat[i][j] = max(mat[i - 1][j], mat[i - 1][j + 1]) + tablero[i][j];
        }
    }
    int max = 0;
    int pos = 0;
    for (int j = 0; j < N; j++)
    {
        if (mat[N - 1][j] > max)
        {
            max = mat[N - 1][j];
            pos = j + 1;
        }
    }

    return {pos, max};
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{

    int N;
    cin >> N;

    if (!std::cin)
        return false;

    Matriz<int> tablero(N, N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> tablero[i][j];
        }
    }

    Solucion sol = maxPuntuacion_optima(N, tablero);
    cout << sol.puntuacion << " " << sol.columna << "\n";

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
