# F - Hangar del SBC: respuesta = contar(B) - contar(A - 1), donde contar(T) = cantidad de formas de elegir
# K cajas con peso total <= T. Con las cajas ordenadas, contar(i, k, T) decide sobre la caja más pesada
# (i - 1): no tomarla o tomarla. Se corta antes cuando:
#   - las k cajas más pesadas disponibles ya caben -> cualquier elección cabe: C(i, k);
#   - las k más livianas no caben -> ninguna cabe: 0.
# Como cada caja pesa al menos el doble que cualquier otra más liviana, en cada paso una de las dos ramas
# termina enseguida y la recursión es casi lineal.
import sys
from math import comb


def main():
    data = sys.stdin.buffer.read().split()
    n, k = int(data[0]), int(data[1])
    p = sorted(map(int, data[2:2 + n]))
    a, b = int(data[2 + n]), int(data[3 + n])

    def contar(i, k, t):
        if k < 0 or t < 0 or i < k:
            return 0
        if k == 0:
            return 1
        if sum(p[i - k:i]) <= t:
            return comb(i, k)
        if sum(p[:k]) > t:
            return 0
        r = contar(i - 1, k, t)
        if t >= p[i - 1]:
            r += contar(i - 1, k - 1, t - p[i - 1])
        return r

    print(contar(n, k, b) - contar(n, k, a - 1))


main()
