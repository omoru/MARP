
#include<iostream>
#include<vector>
#include <fstream>
#include <queue>
#include<climits>
using namespace std;

struct Nodo {
    //vector<int> sol;
    vector<bool> asignados;
    int k;
    double tiempo; // tiempo ocupado
    double tiempo_opt; // estimación, prioridad
    bool operator<(Nodo const& otro) const { return otro.tiempo_opt < tiempo_opt; }
};

/*
int coste_pes(vector<vector<int>>const& datos, Nodo Y ,int n) {

    int pes = 0;
    int trabajador = Y.k + 1;
    for (int i = 0; i < n; i++) {
        if (!Y.asignados[i]) {
            pes += datos[trabajador][i];
            trabajador++;
        }
    }
    return pes;

}
*/

void funcionarios(vector<vector<int>>const& datos, vector<int>const& opt, vector<int>const& pes,
    int n, int& mejor_tiempo, vector<int>& sol_mejor) {

    Nodo Y;
    //Y.sol = vector<int>(n);
    Y.asignados = vector<bool>(n, false);
    Y.k = -1;
    Y.tiempo = 0;
    Y.tiempo_opt = opt[0];
    priority_queue<Nodo> cola;
    cola.push(Y);
    mejor_tiempo = INT_MAX;//NO SE INICIALIZA A PES[0], ya se cambiara en el else

    while (!cola.empty() && cola.top().tiempo_opt <= mejor_tiempo) {
        Y = cola.top(); cola.pop();
        Nodo X(Y);
        X.k += 1;

        //Por cada nivel k (trabajador) decidimos realizar y no realizar la tarea i.
        for (int i = 0; i < n; i++) {
            if (!X.asignados[i]) {
                //X.sol[X.k] = i;
                //marcar -- trabajador k realiza tarea i
                X.asignados[i] = true;
                X.tiempo = Y.tiempo + datos[X.k][i];
                //
                X.tiempo_opt = X.tiempo + opt[X.k];
                if (X.tiempo_opt <= mejor_tiempo) {
                    if (X.k == n - 1) {
                        //sol_mejor = X.sol;
                        mejor_tiempo = X.tiempo;
                    }
                    else {
                        cola.push(X);
                        if (X.tiempo + pes[X.k] < mejor_tiempo)
                            mejor_tiempo = X.tiempo + pes[X.k];

                    }
                }
                //desmarcar -- trabajador k no realiza la tarea i.
                X.asignados[i] = false;

            }
        }
    }
}



bool resuelveCaso() {
    int n;
    cin >> n;
    if (n == 0)
        return false;

    vector<vector<int>> datos(n, vector<int>(n)); //matriz n*n
    vector<int> minimos(n, INT_MAX);// array con el tiempo de la tarea que realiza mas rapido cada trabajador
    vector<int> maximos(n, INT_MIN);// array con el tiempo de la tarea que realiza mas LENTO cada trabajador
    vector<int> opt(n);
    vector<int> pes(n);
    int mejor_tiempo;
    vector<int> sol_mejor(n);


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> datos[i][j];
            if (datos[i][j] < minimos[i])minimos[i] = datos[i][j];
            if (datos[i][j] > maximos[i])maximos[i] = datos[i][j];
        }
    }

    opt[n - 1] = 0; pes[n - 1] = 0;
    for (int i = n - 2; i >= 0; i--) {
        opt[i] = opt[i + 1] + minimos[i + 1];
        pes[i] = pes[i + 1] + maximos[i + 1];
    }

    funcionarios(datos, opt, pes, n, mejor_tiempo, sol_mejor);

    cout << mejor_tiempo << endl;
    //for (int i = 0; i < sol_mejor.size(); i++)
      //  cout << sol_mejor[i] << endl;


    return true;

}
int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    /*srand(time(NULL));
    while (true) resuelveCasoCamion();*/
    while (resuelveCaso());


    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
