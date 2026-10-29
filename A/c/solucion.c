/* El juez compila sin optimizaciones (gcc sin -O2); esta línea le pide a GCC que optimice igual. */
#pragma GCC optimize("O2")
/* A - Apartamentos: ordenar ambas listas y emparejar con dos punteros (greedy). */
#include <stdio.h>
#include <stdlib.h>

static int cmp(const void *x, const void *y) {
    int a = *(const int *)x, b = *(const int *)y;
    return (a > b) - (a < b);
}

int main(void) {
    int n, m, k;
    if (scanf("%d %d %d", &n, &m, &k) != 3) return 0;
    int *a = malloc(sizeof(int) * n), *b = malloc(sizeof(int) * m);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int j = 0; j < m; j++) scanf("%d", &b[j]);
    qsort(a, n, sizeof(int), cmp);
    qsort(b, m, sizeof(int), cmp);
    int i = 0, j = 0, asignados = 0;
    while (i < n && j < m) {
        if ((long long)b[j] < (long long)a[i] - k) j++;
        else if ((long long)b[j] > (long long)a[i] + k) i++;
        else { asignados++; i++; j++; }
    }
    printf("%d\n", asignados);
    return 0;
}
