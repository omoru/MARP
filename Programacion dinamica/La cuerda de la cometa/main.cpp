

//Oscar Morujo Fernandez

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

struct Cuerda
{
    long long int longitud;
    long long int coste;
};

/*
N -> numero de cuerdas
L -> longitud cuerda deseada
li -> longitud de la cuerda i
ci-> coste de la cuerda i
*/

/*numManeras(i,j) : Numero de maneras de conseguir una cuerda de tamaño j teniendo en cuenta las cuerdas de la 1 a la i
    Llamada inicial: numManeras(N,L)
    Casos base:
        numManeras(_,0) = 1
        numManeras(0,_) = 0
    Caso recursivo:
        numManeras(i,j) = numManeras(i-1,j-li) + numManeras (i-1,j)

*/

//Coste en espacio O(NxL), coste en tiempo O(NxL)
long long int numManeras_NxL(int L, const vector<Cuerda> &cuerdas)
{
    long long int n = cuerdas.size();
    Matriz<long long int> mat(n + 1, L + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        mat[i][0] = 1;
        for (int j = 1; j <= L; j++)
        {
            if (cuerdas[i - 1].longitud <= j)
                mat[i][j] = mat[i - 1][j] + mat[i - 1][j - cuerdas[i - 1].longitud];
            else
                mat[i][j] = mat[i - 1][j];
        }
    }
    return mat[n][L];
}

/*Coste en espacio O(L), actualizamos sobre un solo vector de derecha a izquierda para ir dejando a la derecha de la j
    los elementos de la fila i, y a la izquierda manteniendo los de la fila i-1 que no queremos modificar aun, 

    Coste en tiempo O(NxL)

    Igual para los otros 2 problemas
*/
long long int numManeras_L(int L, const vector<Cuerda> &cuerdas)
{
    long long int n = cuerdas.size();
    vector<long long int> mat(L + 1, 0);
    mat[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = L; j >= 1; j--)
        {
            if (cuerdas[i - 1].longitud <= j)
                mat[j] = mat[j] + mat[j - cuerdas[i - 1].longitud];
            //else
            //mat[j]=mat[j];
        }
    }
    return mat[L];
}

/*
minCuerdas(i,j) : Numero minimo de cuerdas para conseguir una de tamaño j teniendo en cuenta las cuerdas de la 1 a la i :
    Llamada inicial: minCuerdas(n,L)
    Casos base:
        minCuerdas(_,0) = 0
        minCuerdas(0,_) = infinito
    Caso recursivo:
        minCuerdas(i,j) = min(minCuerdas(i-1,j-li) + 1 , minCuerdas (i-1,j))

*/

EntInf minCuerdas(int L, const vector<Cuerda> &cuerdas)
{
    long long int n = cuerdas.size();
    vector<EntInf> mat(L + 1, Infinito);
    mat[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = L; j >= 1; j--)
        {
            if (cuerdas[i - 1].longitud <= j)
                mat[j] = min(mat[j], mat[j - cuerdas[i - 1].longitud] + 1);
            //else
            //mat[j]=mat[j];
        }
    }
    return mat[L];
}

/*
minCoste(i,j) : Minimo coste necesario para conseguir una cuerda de tamaño j teniendo en cuenta las cuerdas de la 1 a la i:
    Llamada inicial: minCoste(n,L)
    Casos base:
        minCoste(_,0) = 0
        minCoste(0,_) = infinito
    Caso recursivo:
        minCoste(i,j) = min(minCoste(i-1,j-li) + ci , minCoste (i-1,j))
*/

EntInf minCoste(int L, const vector<Cuerda> &cuerdas)
{
    long long int n = cuerdas.size();
    vector<EntInf> mat(L + 1, Infinito);
    mat[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = L; j >= 1; j--)
        {
            if (cuerdas[i - 1].longitud <= j)
                mat[j] = min(mat[j], mat[j - cuerdas[i - 1].longitud] + cuerdas[i - 1].coste);
            //else
            //mat[j]=mat[j];
        }
    }
    return mat[L];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{

    int N, L;
    cin >> N;
    cin >> L;
    if (!std::cin)
        return false;

    vector<Cuerda> cuerdas(N);
    int longitud, coste;
    for (int i = 0; i < N; i++)
    {
        cin >> longitud >> coste;
        cuerdas[i] = {longitud, coste};
    }

    //Matriz<Solucion> mat(N + 1, L + 1,{-1,Infinito,Infinito});
    //Solucion sol = recursionDesc_1(N, L, cuerdas, mat);

    //Solucion sol = recursionAsc(L, cuerdas);
    long long int num_maneras = numManeras_L(L, cuerdas);
    if (num_maneras == 0)
        cout << "NO\n";
    else
        cout << "SI " << num_maneras << " " << minCuerdas(L, cuerdas) << " " << minCoste(L, cuerdas) << "\n";

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
