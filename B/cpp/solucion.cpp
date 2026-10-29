// El juez compila sin optimizaciones (g++ sin -O2); esta línea le pide a GCC que optimice igual.
#pragma GCC optimize("O2")
// B - Combinaciones de Monedas II: DP de "mochila no acotada" que cuenta combinaciones sin orden.
// dp[s] = formas de formar s con las monedas procesadas; recorrer las monedas en el ciclo externo
// hace que cada combinación se cuente una sola vez. O(n·x).
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (auto &v : c) cin >> v;
    vector<int> dpv(x + 1, 0);
    int *dp = dpv.data();   // puntero crudo: el ciclo interno se ejecuta hasta 10^8 veces
    dp[0] = 1;
    for (int v : c)
        for (int s = v; s <= x; s++) {
            int t = dp[s] + dp[s - v];
            dp[s] = t >= MOD ? t - MOD : t;
        }
    cout << dp[x] << '\n';
}
