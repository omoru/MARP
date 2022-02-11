#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <ostream>
#include "Matriz.h"

using namespace std;
/*

Programacion dinamica ascendente optimizando en espacio

Consideramos que cada pelicula dura 10 minutos mas de lo que dura realmente, ya que entre pelicula y pelicula
deben de pasar 10 minutos, asi, como dice el enunciado que ninguna pelicula acabara mas alla de las 12 de la noche,
en el caso de que una acabe justo a las 12, le habremos puesto que acaba a las 12:10 al añadir 10 minutos de duracion ficticia.
EL tamaño de la tabla sera 24*60 + 10

Ejemplo:
    -Peli 1 : 21:00 90 -> acaba a las 22:30, pero añadiendo los 10 de duracion extra seria a las 22:40
    -Peli 2 : 22:30 80 -> se puede ver , inicio < 22:40, acabaria a las 00:00 pero con la duracion extra seria a las 00:10

N-> numero de peliculas
HMAX-> 60*24 + 10

maxMinutos(i,j) : maximo numero de minutos de ver peliculas posibles considerando las peliculas de la 1 a la i (ordenadas por hora de inicio ascendente)
                    y hasta la hora j.

Casos base:
    maxMinutos(0,j) = 0 con 0 <= j <= HMAX
    maxMinutos(i,0) = 0 con 0 <= i <= N
Caso recursivo:
    maxMinutos(i,j) =   max(maxMinutos(i-1,j),
                            maxMinutos(i-1,peliculas[i].inicio) + peliculas[i].duracion)        si pelicula[i].inicio + pelicula[i].duracion <= j - 10

                            1 < j <= HMAX
                            1 < i <= N

Llamada inicial:
    maxMinutos(N,HMAX)

Espacio adicional: O(N*HMAX) ya que la solucion no es la matriz entera, si no solo una posicion de esta
Tiempo: O(N*HMAX)
*/

struct Pelicula
{
    int hora_inicio;
    int duracion;
};

// Sobrecarga del operador < para ordenar las peliculas
struct
{
    bool operator()(Pelicula a, Pelicula b) const
    {
        return a.hora_inicio < b.hora_inicio;
    }
} customLess;

int maxTiempo(const vector<Pelicula> &peliculas, int numPeliculas)
{
    int numMinutos = 24 * 60 + 10;
    vector<int> tabla(numMinutos + 1, 0);
    for (int i = 1; i <= numPeliculas; i++)
    {
        for (int j = numMinutos; j > 0; j--)
        {
            int duracion = peliculas[i - 1].duracion + 10; // añadimos los 10 minutos a la duracion
            if (peliculas[i - 1].hora_inicio + duracion <= j)
            {
                tabla[j] = max(tabla[j], tabla[peliculas[i - 1].hora_inicio] + peliculas[i - 1].duracion);
            }
        }
    }
    return tabla[numMinutos];
}

bool resuelveCaso()
{
    int numPeliculas;
    cin >> numPeliculas;
    if (numPeliculas == 0)
        return false;
    int hora, minutos, duracion;
    char ignore;
    vector<Pelicula> peliculas;

    for (int i = 0; i < numPeliculas; i++)
    {
        cin >> hora >> ignore >> minutos >> duracion;
        peliculas.push_back({hora * 60 + minutos, duracion});
    }
    sort(peliculas.begin(), peliculas.end(), customLess);

    cout << maxTiempo(peliculas, numPeliculas) << '\n';

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