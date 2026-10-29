/* J - Número de cadenas: s[i..i+2] es palíndromo  <=>  s[i] == s[i+2].
   Las posiciones pares y las impares forman dos cadenas independientes; entre las dos tienen N - 2 pares
   (s[i], s[i+2]) y cada uno puede ser "igual" o "distinto". Elegir cuáles K son iguales: C(N-2, K).
   El primer carácter de cada cadena tiene A opciones, cada par igual 1 y cada par distinto A - 1:
       respuesta = A^2 · (A-1)^(N-2-K) · C(N-2, K)          (N >= 2)
   Con N = 1 no hay subcadenas de largo 3: la respuesta es A si K = 0 y 0 si no. */
#include <stdio.h>

#define MOD 998244353LL

static long long potencia(long long b, long long e) {
    long long r = 1;
    b %= MOD;
    while (e > 0) {
        if (e & 1) r = r * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }
    return r;
}

int main(void) {
    long long n, k, a;
    if (scanf("%lld %lld %lld", &n, &k, &a) != 3) return 0;
    if (n == 1) { printf("%lld\n", k == 0 ? a : 0); return 0; }
    if (k > n - 2) { printf("0\n"); return 0; }
    long long m = n - 2, r = k < m - k ? k : m - k, num = 1, den = 1;
    for (long long i = 0; i < r; i++) {
        num = num * ((m - i) % MOD) % MOD;
        den = den * (i + 1) % MOD;
    }
    long long binom = num * potencia(den, MOD - 2) % MOD;
    printf("%lld\n", a * a % MOD * potencia(a - 1, m - k) % MOD * binom % MOD);
    return 0;
}
