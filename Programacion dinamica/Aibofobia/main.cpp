

// Oscar Morujo Fernandez

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include "Matriz.h"

using namespace std;

struct Solucion
{
    int min_num_letras;
    string palindromo;
};

/*

Programacion dinamica descendente ya que no es posible reducir coste en espacio si queremos reconstruir la solucion y usar ascendente
no nos proporciona ningun beneficio.

minNumLetras(i,j) : minimo numero de letras que hay que añadir para formar un palindromo teniendo en cuenta las letras de la i a la j

N-> longitud(palabra)
Casos base:
    minNumLetras(i,i) = 0 con 0 <= i < N
    minNumLetras(i,j) = 0 con i > j
Caso recursivo:
    minNumLetras(i,j) = minNumLetras(i+1,j-1)   si palabra[i]== palabra[j]
                     eoc -> min(minNumLetras(i+1,j),minNumLetras(i,j-1)) + 1

Llamada inicial:
    minNumLetras(0,N-1)

Espacio: O(N^2)
Tiempo: O(N^2)
*/

int minNumLetras(const string &palabra, int i, int j, Matriz<int> &mat)
{
    int &res = mat[i][j];
    if (res != -1)
        return res;
    if (i == j)
        return 0;
    if (i > j)
        return 0;
    else
    {
        if (palabra[i] == palabra[j])
            res = minNumLetras(palabra, i + 1, j - 1, mat);
        else
            res = 1 + min(minNumLetras(palabra, i + 1, j, mat), minNumLetras(palabra, i, j - 1, mat));
    }
    return res;
}

// Version ascendente del algoritmo : se recorre por diagonales el triangulo superior de la matriz y de arriba a abajo.
int minNumLetras_ascendente(const string &palabra, Matriz<int> &mat)
{
    int n = palabra.size();
    for (int d = 1; d < n; d++)
    { // recorrido diagonal d
        int i;
        for (int j = d; j < n; j++)
        {
            i = j - d;
            if (palabra[i] == palabra[j])
                mat[i][j] = mat[i + 1][j - 1];
            else
            {
                mat[i][j] = 1 + min(mat[i + 1][j], mat[i][j - 1]);
            }
        }
    }
    return mat[0][n - 1];
}

// Tiempo O(N): lineal en la longitud de la palabra
// Añade al final de sol el palindromo mas largo en palabra[i..j]
void reconstruye_solucion(const string &palabra, Matriz<int> &mat, int i, int j, string &sol)
{
    if (i > j)
        return;
    if (i == j)
        sol.push_back(palabra[i]);
    else if (palabra[i] == palabra[j])
    { // si los extremos son iguales,se añade el izq final,se reconstruye lo del medio recursivamente y se añade el derecho por le final
        sol.push_back(palabra[i]);
        reconstruye_solucion(palabra, mat, i + 1, j - 1, sol);
        sol.push_back(palabra[j]);
    }
    else if (mat[i][j] == mat[i + 1][j] + 1)
    { // si los extremos eran diferentes, se añade el izq final,se reconstruye lo del medio recursivamente y se añade el izq otra vez por le final
        sol.push_back(palabra[i]);
        reconstruye_solucion(palabra, mat, i + 1, j, sol);
        sol.push_back(palabra[i]);
    }
    else
    { // si los extremos eran diferentes, se añade el dcha final,se reconstruye lo del medio recursivamente y se añade el dcha otra vez por le final
        sol.push_back(palabra[j]);
        reconstruye_solucion(palabra, mat, i, j - 1, sol);
        sol.push_back(palabra[j]);
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{

    string palabra;
    cin >> palabra;

    if (!std::cin)
        return false;

    int N = palabra.length();

    Matriz<int> mat(N, N, -1);
    cout << minNumLetras(palabra, 0, N - 1, mat) << " ";

    // Matriz<int> mat(N, N, 0);
    // cout<<minNumLetras_ascendente(palabra,mat) << " ";

    string sol;
    reconstruye_solucion(palabra, mat, 0, N - 1, sol);
    cout << sol << '\n';

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
