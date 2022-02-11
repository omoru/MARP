

// Oscar Morujo Fernandez

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include "Matriz.h"

using namespace std;

/*

Programacion dinamica descendente ya que no es posible reducir coste en espacio si queremos reconstruir la solucion y usar ascendente
no nos proporciona ningun beneficio.

maxSubsecuencia(i,j) : longitud de la subsecuencia mas larga teniendo en cuenta las letras de la 1 a la i de la palabra 1 y
                        las letras de la 1 a la j de la palabra 2.

N1-> longitud(palabra1)
N2-> longitud(palabra2)

Casos base:
    maxSubsecuencia(0,j) = 0 con 0 <= j <= N2
    maxSubsecuencia(i,0) = 0 con 0 <= i <= N1
Caso recursivo:
    maxSubsecuencia(i,j) = maxSubsecuencia(i-1,j-1) + 1   si palabra1[i]== palabra2[j]
                     eoc -> max(maxSubsecuencia(i-1,j),maxSubsecuencia(i,j-1))

Llamada inicial:
    maxSubsecuencia(N1,N2)

Espacio: O(N1*N2)
Tiempo: O(N1*N2)
*/

// Version descendente del algortimo
int maxSubsecuencia(const string &palabra1, const string &palabra2, int i, int j, Matriz<int> &mat)
{
    int &res = mat[i][j];
    if (res != -1)
        return res;
    if (i == 0 || j == 0)
        res = 0;
    else if (palabra1[i - 1] == palabra2[j - 1])
        res = 1 + maxSubsecuencia(palabra1, palabra2, i - 1, j - 1, mat);
    else
        res = max(maxSubsecuencia(palabra1, palabra2, i - 1, j, mat), maxSubsecuencia(palabra1, palabra2, i, j - 1, mat));

    return res;
}

// Version ascendente del algoritmo : se recorre por filas la matriz  de izquierda a derecha y de arriba a abajo
int maxSubsecuencia_ascendente(const string &palabra1, const string &palabra2, Matriz<int> &mat)
{
    int n1 = palabra1.size();
    int n2 = palabra2.size();
    for (int i = 1; i < n1 + 1; i++)
    {
        for (int j = 1; j < n2 + 1; j++)
        {
            if (palabra1[i - 1] == palabra2[j - 1])
                mat[i][j] = mat[i - 1][j - 1] + 1;
            else
                mat[i][j] = max(mat[i - 1][j], mat[i][j - 1]);
        }
    }
    return mat[n1][n2];
}

// Tiempo O(N): en el peor caso lineal en el numero de caracteres de la palabra mas larga
// Añade al final de sol la subsecuencia mas larga en palabra[i..j]
void reconstruye_solucion(const string &palabra1, const string &palabra2, Matriz<int> &mat, string &sol)
{
    int n1 = palabra1.size();
    int n2 = palabra2.size();
    int i = n1, j = n2;
    while (mat[i][j] > 0)
    {
        if (palabra1[i - 1] == palabra2[j - 1])
        {
            sol.push_back(palabra1[i - 1]);
            i--;
            j--;
        }
        else
        {
            if (mat[i - 1][j] == mat[i][j - 1] || mat[i][j] == mat[i - 1][j])
                i--;
            else
                j--;
        }
    }

    // reverse
    int longitud = sol.size() - 1;
    for (int i = longitud; i > longitud / 2; i--)
    {
        char aux = sol[i];
        sol[i] = sol[longitud - i];
        sol[longitud - i] = aux;
    }
}

void reconstruye_solucion_recursiva(const string &palabra1, const string &palabra2, Matriz<int> &mat, string &sol, int i, int j)
{
    if (mat[i][j] == 0)
    {
        return;
    }
    if (palabra1[i - 1] == palabra2[j - 1])
    {
        reconstruye_solucion_recursiva(palabra1, palabra2, mat, sol, i - 1, j - 1);
        sol.push_back(palabra1[i - 1]);
    }
    else
    {
        if (mat[i - 1][j] == mat[i][j - 1] || mat[i][j] == mat[i - 1][j])
            reconstruye_solucion_recursiva(palabra1, palabra2, mat, sol, i - 1, j);
        else
            reconstruye_solucion_recursiva(palabra1, palabra2, mat, sol, i, j - 1);
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{

    string palabra1, palabra2;
    cin >> palabra1;

    if (!std::cin)
        return false;

    cin >> palabra2;
    int N1 = palabra1.size();
    int N2 = palabra2.size();
    Matriz<int> mat(N1 + 1, N2 + 1, -1);
    int res = maxSubsecuencia(palabra1, palabra2, N1, N2, mat);

    // Matriz<int> mat(N1 + 1, N2 + 1, 0);
    // int res = maxSubsecuencia_ascendente(palabra1, palabra2, mat);
    // cout << res << " ";

    string sol;
    reconstruye_solucion(palabra1, palabra2, mat, sol);
    // reconstruye_solucion_recursiva(palabra1, palabra2, mat, sol, N1 , N2 );
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
