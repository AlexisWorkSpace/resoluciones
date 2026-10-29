# E - Viajes en Ascensor: DP sobre subconjuntos. Para cada conjunto de personas ya subidas,
# dp[mask] = (mínimo de viajes, menor peso en el último viaje). Se prueba agregar a cada persona del conjunto.
# Nota: son O(2^n · n) ≈ 2·10^7 pasos para n = 20; en Python no entra en 1 s para los casos máximos.
import sys


def main():
    data = sys.stdin.buffer.read().split()
    n, x = int(data[0]), int(data[1])
    w = list(map(int, data[2:2 + n]))
    total = 1 << n
    viajes = [0] * total
    ultimo = [0] * total
    viajes[0], ultimo[0] = 1, 0
    for mask in range(1, total):
        mejor_v, mejor_u = n + 1, 0
        resto = mask
        while resto:
            bit = resto & -resto
            resto ^= bit
            i = bit.bit_length() - 1
            prev = mask ^ bit
            v, u = viajes[prev], ultimo[prev]
            if u + w[i] <= x:
                u += w[i]
            else:
                v += 1
                u = w[i]
            if v < mejor_v or (v == mejor_v and u < mejor_u):
                mejor_v, mejor_u = v, u
        viajes[mask], ultimo[mask] = mejor_v, mejor_u
    print(viajes[total - 1])


main()
