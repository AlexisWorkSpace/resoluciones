# J - Número de cadenas: s[i..i+2] es palíndromo  <=>  s[i] == s[i+2].
# Las posiciones pares y las impares forman dos cadenas independientes; entre las dos tienen N - 2 pares
# (s[i], s[i+2]) y cada uno puede ser "igual" o "distinto". Elegir cuáles K son iguales: C(N-2, K).
# El primer carácter de cada cadena tiene A opciones, cada par igual 1 y cada par distinto A - 1:
#     respuesta = A^2 · (A-1)^(N-2-K) · C(N-2, K)          (N >= 2)
# Con N = 1 no hay subcadenas de largo 3: la respuesta es A si K = 0 y 0 si no.
MOD = 998244353

n, k, a = map(int, input().split())
if n == 1:
    print(a % MOD if k == 0 else 0)
elif k > n - 2:
    print(0)
else:
    m = n - 2
    r = min(k, m - k)
    num = den = 1
    for i in range(r):
        num = num * (m - i) % MOD
        den = den * (i + 1) % MOD
    binom = num * pow(den, MOD - 2, MOD) % MOD
    print(a * a % MOD * pow(a - 1, m - k, MOD) % MOD * binom % MOD)
