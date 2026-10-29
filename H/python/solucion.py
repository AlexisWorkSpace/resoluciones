# H - Números de Fibonacci: "fast doubling", O(log n).
#   F(2k)   = F(k) · (2·F(k+1) − F(k))
#   F(2k+1) = F(k)^2 + F(k+1)^2
MOD = 10**9 + 7


def fib(n):
    """Devuelve (F(n), F(n+1)) módulo MOD."""
    if n == 0:
        return 0, 1
    a, b = fib(n >> 1)
    c = a * ((2 * b - a) % MOD) % MOD
    d = (a * a + b * b) % MOD
    return (d, (c + d) % MOD) if n & 1 else (c, d)


print(fib(int(input()))[0])
