//Oscar Morujo Fernandez

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"
#include <algorithm>

using namespace std;

/*
N -> numero de tipos de monedas
C -> cantidad a pagar
vi -> valor de la moneda de tipo i
ci -> cantidad disponible de monedas de tipo i

Usaremos programacion dinamica ascendente para optimizar el uso de memoria

minMonedas(i,j): numero minimo necesario de monedas para pagar la cantidad j 
                 teniendo en cuenta los tipos de monedas de la 1 a la i

    Llamada inicial:
        minMonedas(N,C)
    Casos base:
        minMonedas(0,j) = Infinito     si 1 <= j <= C
        minMonedas(i,0) = 0            si 0 <= i <= N

    Casos recursivos:
        1 <= i <= N
        1 <= j <= C
        Version 1 :minMonedas(i,j)= min 1<= k <=ci (minMonedas(i-1,j),minMonedas(i-1,j- vi*k) + k) 
        Version 2: minMonedas(i,j) = min(minMonedas(i-1,j),minMonedas(i,j-vi) + 1)  si ci >0

    Con las dos versiones nos supone un espacio adicional en O(C), ya que solo necesitamos la fila
    i y la i -1 para ir calculando la matriz,y se puede actualizar sobre una unica fila de derecha a
    izquierda ya que de la fila i - 1 solo necesitaremos las columnas que sean < = j
    y no queremos pisar esos valores
    
    Tiempo: O(N x C x max{ni}) siendo ni las cantidades de monedas de cada tipo
    Espacio : O(C)
*/


EntInf minMonedas(int C, const vector<int> &valores,const vector<int> &cantidades)
{
    int n = valores.size();
    vector<EntInf> mat(C + 1, Infinito);
    mat[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = C;j > 0;j--)
        {
            for(int k = 1; k <= cantidades[i-1] && k *valores[i-1] <= j;k++){
                int vi = k*valores[i-1];
                if(mat[j-vi]!= Infinito) 
                    mat[j]=min(mat[j],mat[j-vi] + k);
                else
                   mat[j]=mat[j] ;
            }
        }
    }

    return mat[C];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{

    int tiposMonedas;
    cin >> tiposMonedas;
    
    if (!std::cin)
        return false;

    vector<int> valores(tiposMonedas);
    for (int i = 0; i < tiposMonedas; i++)
    {
        cin >> valores[i];
    }
    vector<int> disponibles(tiposMonedas);

      for (int i = 0; i < tiposMonedas; i++)
    {
        cin >> disponibles[i];
    }

    int precio;
    cin>>precio;
    
    EntInf num_monedas = minMonedas(precio,valores,disponibles);
    if (num_monedas == Infinito)
        cout << "NO\n";
    else
    {
              cout << "SI "<<num_monedas<<'\n';
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
