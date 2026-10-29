/* El juez compila sin optimizaciones (gcc sin -O2); esta línea le pide a GCC que optimice igual. */
#pragma GCC optimize("O2")
/* E - Viajes en Ascensor: DP sobre subconjuntos. Para cada conjunto de personas ya subidas,
   dp[mask] = (mínimo de viajes, menor peso en el último viaje). O(2^n · n). */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    long long x, w[20];
    if (scanf("%d %lld", &n, &x) != 2) return 0;
    for (int i = 0; i < n; i++) scanf("%lld", &w[i]);
    int total = 1 << n;
    int *viajes = malloc(sizeof(int) * total);
    long long *ultimo = malloc(sizeof(long long) * total);
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
    printf("%d\n", viajes[total - 1]);
    return 0;
}
