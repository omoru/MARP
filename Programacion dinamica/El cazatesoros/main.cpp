

// Oscar Morujo Fernandez

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include "Matriz.h"

using namespace std;

struct Cofre
{
    int profundidad;
    int cantidad_oro;
};

struct Solucion
{
    int max_oro;
    int num_cofres;
    list<int> cofres;
};

/*

Programacion dinamica descendente ya que no es posible reducir coste en espacio si queremos reconstruir la solucion

maxGanancia(i,j) : maxima ganancia posible teniendo j segundos restantes de oxigeno y considerando los cofres del 1 al i

N -> numero de cofres
T -> tiempo de oxigeno restante
pi-> profundidad del cofre i
ti -> tiempo necesario para coger el cofre i (2pi + pi = 3pi)

Casos base:
    maxGanancia(0,j) = 0 con 0 <= j<= T
    maxGanancia(i,0) = 0 con 0 < i <= N
Caso recursivo:
    maxGanancia(i,j) = max(maxGanancia(i-1,j),maxGanancia(i-1,j-(3*pi))

Llamada inicial:
    maxGanancia(N,T)

Espacio: O(NxT)
Tiempo: O(NxT)
*/

int maxGanancia(const vector<Cofre> &cofres, int i, int j, Matriz<int> &mat)
{
    int &res = mat[i][j];
    if (res != -1)
        return res;
    if (i == 0 || j == 0)
        res = 0;
    else
    {
        int ti = 3 * cofres[i - 1].profundidad;
        if (ti > j)
            res = maxGanancia(cofres, i - 1, j, mat);
        else
            res = max(maxGanancia(cofres, i - 1, j, mat), maxGanancia(cofres, i - 1, j - ti, mat) + cofres[i - 1].cantidad_oro);
    }
    return res;
}

// v1: con list
Solucion resuelve(const vector<Cofre> &cofres, int T)
{

    int n = cofres.size();
    Matriz<int> mat(n + 1, T + 1, -1);
    int max_ganancia = maxGanancia(cofres, n, T, mat);
    /*Reconstruccion solucion:
        Tiempo O(N) en el peor caso, pero al ir reduciendo en 3*pi daria menos iteraciones
    */
    list<int> sol;
    int i = n;
    int j = T;
    while (i > 0 && j > 0)
    {
        if (mat[i][j] != mat[i - 1][j])
        { //--> mat[i][j] == mat[i-1][j -3*pi]
            sol.push_front(i - 1);
            j -= 3 * cofres[i - 1].profundidad;
        }
        i--;
    }

    return {max_ganancia, sol.size(), sol};
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{

    int N, T;
    cin >> T;

    if (!std::cin)
        return false;
    cin >> N;
    vector<Cofre> cofres;
    int profundidad, oro;
    for (int i = 0; i < N; i++)
    {
        cin >> profundidad;
        cin >> oro;
        cofres.push_back({profundidad, oro});
    }

    Solucion sol = resuelve(cofres, T);
    cout << sol.max_oro << "\n";
    cout << sol.num_cofres << "\n";
    for (int i : sol.cofres)
        cout << cofres[i].profundidad << " " << cofres[i].cantidad_oro << '\n';

    cout << "---\n";
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
