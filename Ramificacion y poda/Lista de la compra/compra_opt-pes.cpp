#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Nodo {
	vector<int> sol;
	int k;
	vector<int> marcaje;
	double beneficio; // valor acumulado
	double beneficio_opt; // prioridad
	bool operator<(Nodo const& otro) const {
		return otro.beneficio_opt < beneficio_opt;
	}
};




void compra_rp(vector<vector<int>> const& objetos, int m,
	vector<int> sol_mejor, vector<int> opt, vector<int> pes, int& coste_mejor) {
	int N = pes.size();
	// se genera la raíz
	Nodo Y;
	Y.marcaje = vector<int>(m, 3);
	Y.sol = vector<int>(N);
	Y.k = -1;
	Y.beneficio = 0;
	Y.beneficio_opt = opt[0];
	priority_queue<Nodo> cola;
	cola.push(Y);
	coste_mejor = INT_MAX;

	// búsqueda mientras pueda haber algo mejor
	while (!cola.empty() && cola.top().beneficio_opt <= coste_mejor) {

		Y = cola.top();
		cola.pop();
		Nodo X(Y);
		++X.k;

		// probamos a comprar el objeto en cada supermercado.
		for (int i = 0; i < m; i++) {
			if (X.marcaje[i] > 0) {
				//marcamos
				X.marcaje[i]--;
				X.sol[X.k] = i;
				X.beneficio = Y.beneficio + objetos[i][X.k];
				X.beneficio_opt = X.beneficio + opt[X.k];
				if (X.beneficio_opt <= coste_mejor) {
					if (X.k == N - 1) {
						//if (X.beneficio <= coste_mejor) {
						sol_mejor = X.sol;
						coste_mejor = X.beneficio;
						//}
					}
					else {
						cola.push(X);
						int pesimista = X.beneficio + pes[X.k];
						if (pesimista < coste_mejor) {
							coste_mejor = pesimista;
						}
					}
				}
				//desmarcamos
				X.marcaje[i]++;
			}
		}

	}
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

	int nProd, mSuper;
	cin >> mSuper >> nProd;

	vector<vector<int>> datos(mSuper, vector<int>(nProd));
	vector<int> minimos(nProd, INT_MAX);
	vector<int> maximos(nProd, INT_MIN);
	vector<int> opt(nProd);
	vector<int> pes(nProd);

	for (int i = 0; i < mSuper; i++) {
		for (int j = 0; j < nProd; j++) {
			cin >> datos[i][j];
			if (datos[i][j] < minimos[j]) minimos[j] = datos[i][j];
			if (datos[i][j] > maximos[j]) maximos[j] = datos[i][j];
		}
	}

	opt[nProd - 1] = 0; pes[nProd - 1] = 0;
	for (int i = nProd - 2; i >= 0; i--) {
		opt[i] = opt[i + 1] + minimos[i + 1];
		pes[i] = pes[i + 1] + maximos[i + 1];
	}
	vector<int> sol(nProd);
	int coste_mejor;
	compra_rp(datos, mSuper, sol, opt, pes, coste_mejor);
	cout << coste_mejor << '\n';
}



int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}