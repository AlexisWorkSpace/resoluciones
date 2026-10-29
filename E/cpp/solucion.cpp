// El juez compila sin optimizaciones (g++ sin -O2); esta línea le pide a GCC que optimice igual.
#pragma GCC optimize("O2")
// E - Viajes en Ascensor: DP sobre subconjuntos. Para cada conjunto de personas ya subidas,
// dp[mask] = (mínimo de viajes, menor peso en el último viaje). O(2^n · n).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long x;
    cin >> n >> x;
    long long w[20];
    for (int i = 0; i < n; i++) cin >> w[i];
    int total = 1 << n;
    // Dos arreglos simples en vez de vector<pair>: el ciclo interno se ejecuta unas 2·10^7 veces.
    vector<int> viajesV(total);
    vector<long long> ultimoV(total);
    int *viajes = viajesV.data();
    long long *ultimo = ultimoV.data();
    viajes[0] = 1;
    ultimo[0] = 0;
    for (int mask = 1; mask < total; mask++) {
        int mejorV = n + 1;
        long long mejorU = 0;
        for (int i = 0; i < n; i++) {
            if (!(mask >> i & 1)) continue;
            int prev = mask ^ (1 << i);
            int v = viajes[prev];
            long long u = ultimo[prev];
            if (u + w[i] <= x) u += w[i];
            else { v++; u = w[i]; }
            if (v < mejorV || (v == mejorV && u < mejorU)) { mejorV = v; mejorU = u; }
        }
        viajes[mask] = mejorV;
        ultimo[mask] = mejorU;
    }
    cout << viajes[total - 1] << '\n';
}
