/* F - Hangar del SBC: respuesta = contar(B) - contar(A - 1), donde contar(T) = cantidad de formas de elegir
   K cajas con peso total <= T. Con las cajas ordenadas, contar(i, k, T) decide sobre la caja más pesada
   (i - 1): no tomarla o tomarla. Se corta antes cuando:
     - las k cajas más pesadas disponibles ya caben -> cualquier elección cabe: C(i, k);
     - las k más livianas no caben -> ninguna cabe: 0.
   Como cada caja pesa al menos el doble que cualquier otra más liviana, en cada paso una de las dos ramas
   termina enseguida y la recursión es casi lineal.
   Las sumas se cortan apenas superan T (T <= 2·10^18), así nunca desbordan un long long. */
#include <stdio.h>
#include <stdlib.h>

static long long p[50], C[51][51];

static int cmp(const void *x, const void *y) {
    long long a = *(const long long *)x, b = *(const long long *)y;
    return (a > b) - (a < b);
}

/* 1 si la suma de p[desde..hasta) es <= t */
static int cabe(int desde, int hasta, long long t) {
    long long s = 0;
    for (int j = desde; j < hasta; j++) {
        s += p[j];
        if (s > t) return 0;
    }
    return 1;
}

static long long contar(int i, int k, long long t) {
    if (k < 0 || t < 0 || i < k) return 0;
    if (k == 0) return 1;
    if (cabe(i - k, i, t)) return C[i][k];
    if (!cabe(0, k, t)) return 0;
    long long r = contar(i - 1, k, t);
    if (t >= p[i - 1]) r += contar(i - 1, k - 1, t - p[i - 1]);
    return r;
}

int main(void) {
    int n, k;
    long long a, b;
    if (scanf("%d %d", &n, &k) != 2) return 0;
    for (int i = 0; i < n; i++) scanf("%lld", &p[i]);
    scanf("%lld %lld", &a, &b);
    qsort(p, n, sizeof(long long), cmp);
    for (int i = 0; i <= 50; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = C[i - 1][j - 1] + (j < i ? C[i - 1][j] : 0);
    }
    printf("%lld\n", contar(n, k, b) - contar(n, k, a - 1));
    return 0;
}
