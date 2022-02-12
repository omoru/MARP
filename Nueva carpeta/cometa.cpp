#include <iostream>
#include <vector>
#include "Matriz.h"


using namespace std;

int esPosible(string const cadena) {
    int n = cadena.size();

    Matriz<bool> A(n, n, false);
    Matriz<bool> B(n, n, false);
    Matriz<bool> C(n, n, false);

    //CASOS BASE
    for (int i = 0; i < n; i++) {
       
        if (cadena[i] == 'a') A[i][i] = true;
        if (cadena[i] == 'b') B[i][i] = true;
        if (cadena[i] == 'c') C[i][i] = true;
    }

    for (int d = 0; d < n - 1; ++d) {// recorre diagonales
        for (int i = 0; i < n - d; ++i) { // recorre elementos de diagonal
            int j = i + d;
            for (int k = i ; k < j +1; ++k) {
               //FORMAS DE A (AxC, BxC, CxA)
               if ((A[i][k] && C[k + 1][j]) || (B[i][k] && C[k + 1][j]) || (C[i][k] && A[k+1][j])) A[i][j] = true;
               //FORMAS DE B (AxA, AxB, BxB)
               if ((A[i][k] && A[k+1][j]) || (A[i][k] && B[k+1][j]) || (B[i][k] && B[k+1][j])) B[i][j] = true;
               //FORMAS DE C (BxA, CxB, CxC)
               if((B[i][k] && A[k+1][j]) || (C[i][k] && B[k+1][j]) || (C[i][k] && C[k+1][j])) C[i][j] = true;
       
            }
          
        }
    }
    return A[0][n-1];
}

bool resuelveCaso() {
    string cadena;
    cin >> cadena;

    if (!std::cin) return false;

    if (esPosible(cadena)) cout << "SI\n";
    else cout << "NO\n";

    return true;
}

int main() {

    while (resuelveCaso());
    return 0;
}