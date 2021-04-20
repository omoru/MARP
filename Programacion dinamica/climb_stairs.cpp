
using namespace std;
/*
1-Funcion objetivo:
    f(i) es el numero de maneras distintas de llegar al escalón i-esimo
2-Casos base:
    f(0) = 1
    f(1) = 1
3-Relación recurrente:
    f(n) = f(n-1) + f(n-2)
    Al final, se puede llegar desde el escalon n-1 o el n-2, y asi haia atras
4- El orden de ejecucion en ascendente, va de los problemas más pequeños a los grandes
5-La respuesta es f(n)

*/


int climb(int n){
    int *dp = new int(n);
    dp[0] = 1;
    dp[1] = 1;
    for(int i =2; i <= n;i++)
        dp[i] = dp[i-1] + dp[1-2];
        
    int ret = dp[n];
    delete [] dp;
    return ret;
}

int main(){

    climb(3);

    return 0;

}