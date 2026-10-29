# B - Combinaciones de Monedas II: DP de "mochila no acotada" que cuenta combinaciones sin orden.
# dp[s] = formas de formar s con las monedas procesadas hasta ahora. Recorrer las monedas en el ciclo
# externo hace que cada combinación se cuente una sola vez (2+2+5 y 5+2+2 son la misma).
# Nota: son O(n·x) = 10^8 operaciones en el peor caso; en Python no entra en 1 s para los casos máximos.
import sys

MOD = 10**9 + 7


def main():
    data = sys.stdin.buffer.read().split()
    n, x = int(data[0]), int(data[1])
    monedas = list(map(int, data[2:2 + n]))
    dp = [0] * (x + 1)
    dp[0] = 1
    for c in monedas:
        for s in range(c, x + 1):
            dp[s] = (dp[s] + dp[s - c]) % MOD
    print(dp[x])


main()
