/* El juez compila sin optimizaciones (gcc sin -O2); esta línea le pide a GCC que optimice igual. */
#pragma GCC optimize("O2")
/* B - Combinaciones de Monedas II: DP de "mochila no acotada" que cuenta combinaciones sin orden.
   dp[s] = formas de formar s con las monedas procesadas; recorrer las monedas en el ciclo externo
   hace que cada combinación se cuente una sola vez. O(n·x). */
#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main(void) {
    int n, x;
    if (scanf("%d %d", &n, &x) != 2) return 0;
    int *c = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);
    int *dp = calloc(x + 1, sizeof(int));
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        int v = c[i];
        for (int s = v; s <= x; s++) {
            int t = dp[s] + dp[s - v];
            dp[s] = t >= MOD ? t - MOD : t;
        }
    }
    printf("%d\n", dp[x]);
    return 0;
}
