// J - Número de cadenas: s[i..i+2] es palíndromo  <=>  s[i] == s[i+2].
// Las posiciones pares y las impares forman dos cadenas independientes; entre las dos tienen N - 2 pares
// (s[i], s[i+2]) y cada uno puede ser "igual" o "distinto". Elegir cuáles K son iguales: C(N-2, K).
// El primer carácter de cada cadena tiene A opciones, cada par igual 1 y cada par distinto A - 1:
//     respuesta = A^2 · (A-1)^(N-2-K) · C(N-2, K)          (N >= 2)
// Con N = 1 no hay subcadenas de largo 3: la respuesta es A si K = 0 y 0 si no.
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

long long potencia(long long b, long long e) {
    long long r = 1;
    b %= MOD;
    for (; e > 0; e >>= 1, b = b * b % MOD)
        if (e & 1) r = r * b % MOD;
    return r;
}

int main() {
    long long n, k, a;
    cin >> n >> k >> a;
    if (n == 1) { cout << (k == 0 ? a : 0) << '\n'; return 0; }
    if (k > n - 2) { cout << 0 << '\n'; return 0; }
    long long m = n - 2, r = min(k, m - k), num = 1, den = 1;
    for (long long i = 0; i < r; i++) {
        num = num * ((m - i) % MOD) % MOD;
        den = den * (i + 1) % MOD;
    }
    long long binom = num * potencia(den, MOD - 2) % MOD;
    cout << a * a % MOD * potencia(a - 1, m - k) % MOD * binom % MOD << '\n';
}
