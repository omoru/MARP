

//Oscar Morujo Fernandez

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"
#include <algorithm>

using namespace std;

/*
N -> numero de zonas de la diana
C -> puntuacion a alcanzar
vi -> valor de la zona i de la diana
*/

/*

Usaremos programacion dinamica ascendente para optimizar el uso de memoria

minDardos(i,j) : Numero minimo de dardos para conseguir una puntuacion j teniendo en cuenta las 
zonas de la diana de la 1 a la i :
    Llamada inicial: minDardos(N,C)
    Casos base:
        minDardos(_,0) = 0
        minDardos(0,_) = infinito
    Caso recursivo:
        minDardos(i,j) = min(minDardos(i,j-vi) + 1, minDardos (i-1,j))

*/

/*
Tiempo : O(NxC) para llenado de matriz y O(NxC) en el peor caso para reconstruir la solucion
Espacio :O(C), se va modificando el vector de izquierda a derecha dejando a la izquierda de la j
los valores pertenecientes a la nueva fila i, y a la derecha los pertenecientes a la fila i-1
*/
vector<int> minDardos(int C, const vector<int> &zonas)
{
    int n = zonas.size();
    vector<EntInf> mat(C + 1, Infinito);
    mat[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = zonas[i - 1]; j <= C; j++)
        {
            if (zonas[i - 1] <= j)
                mat[j] = min(mat[j], mat[j - zonas[i - 1]] + 1);
            //else
            //mat[j]=mat[j];
        }
    }
    vector<int> sol;
    if (mat[C] != Infinito)
    {
        int i = n, j = C;
        while (j > 0)
        {
            if (zonas[i - 1] <= j && mat[j] == mat[j - zonas[i - 1]] + 1)
            {
                sol.push_back(zonas[i - 1]);
                j = j - zonas[i - 1];
            }
            else
                i--;
        }
    }

    return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{

    int C, N;
    cin >> C;
    cin >> N;
    if (!std::cin)
        return false;

    vector<int> zonas(N);
    for (int i = 0; i < N; i++)
    {
        cin >> zonas[i];
    }

    sort(zonas.begin(), zonas.end()); // Para en caso de empate mostrar el que tenga mayor puntuacion
    vector<int> dardos = minDardos(C, zonas);
    if (dardos.size() == 0)
        cout << "Imposible\n";
    else
    {
        cout << dardos.size() << ":";
        for (int zona : dardos)
        {
            cout << " " << zona;
        }
        cout << "\n";
    }

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