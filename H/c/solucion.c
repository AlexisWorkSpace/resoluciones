/* H - Números de Fibonacci: "fast doubling", O(log n).
     F(2k)   = F(k) · (2·F(k+1) − F(k))
     F(2k+1) = F(k)^2 + F(k+1)^2 */
#include <stdio.h>

#define MOD 1000000007LL

/* Deja en *f = F(n) y *g = F(n+1), módulo MOD. */
static void fib(long long n, long long *f, long long *g) {
    if (n == 0) { *f = 0; *g = 1; return; }
    long long a, b;
    fib(n >> 1, &a, &b);
    long long c = a * ((2 * b - a + MOD) % MOD) % MOD;
    long long d = (a * a + b * b) % MOD;
    if (n & 1) { *f = d; *g = (c + d) % MOD; }
    else { *f = c; *g = d; }
}

int main(void) {
    long long n, f, g;
    if (scanf("%lld", &n) != 1) return 0;
    fib(n, &f, &g);
    printf("%lld\n", f);
    return 0;
}
