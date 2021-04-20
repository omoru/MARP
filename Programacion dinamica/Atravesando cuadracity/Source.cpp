
#include<iostream>
#include<vector>
#include <fstream>

using namespace std;

int cuadracity(vector<vector<bool>> const& grid, int n_oeste_este, int m_norte_sur) {
    vector<vector<int>> M(n_oeste_este, vector<int>(m_norte_sur));
    M[0][0] = 1;
    for (int i = 0; i < n_oeste_este; i++) {
        for (int j = 0; j < m_norte_sur; j++) {
            if (grid[i][j]) {
                if (i > 0 && j > 0)
                    M[i][j] = M[i - 1][j] + M[i][j - 1];
                else if (i > 0)
                    M[i][j] = M[i - 1][j];
                else if (j > 0)
                    M[i][j] = M[i][j - 1];

            }
            else M[i][j] = 0;
           
        }
    }
    return M[n_oeste_este - 1][m_norte_sur-1];
}
bool resuelveCaso() {
    int N_oeste_este;
    int M_norte_sur;
    int pos_hermano;
    cin >> N_oeste_este;
    if (!std::cin)  // fin de la entrada
        return false;
    cin>> M_norte_sur;
    vector<vector<bool>> grid(N_oeste_este, vector<bool>(M_norte_sur));
    char c;
    for (int i = 0; i < N_oeste_este; i++) {
        for (int j = 0; j < M_norte_sur; j++) {
            cin >> c;;
            //No es seguro
            if (c == 'P')
                grid[i][j] = false;
            else grid[i][j] = true; // es seguro
        }
    }

    
    int res = cuadracity(grid, N_oeste_este, M_norte_sur);
    cout << res << endl;
    return true;

}
int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
