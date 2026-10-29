# A - Apartamentos: ordenar ambas listas y emparejar con dos punteros (greedy).
import sys


def main():
    data = sys.stdin.buffer.read().split()
    n, m, k = int(data[0]), int(data[1]), int(data[2])
    a = sorted(map(int, data[3:3 + n]))
    b = sorted(map(int, data[3 + n:3 + n + m]))
    i = j = asignados = 0
    while i < n and j < m:
        if b[j] < a[i] - k:      # apartamento demasiado chico para todos los que quedan
            j += 1
        elif b[j] > a[i] + k:    # ningún apartamento restante sirve a este solicitante
            i += 1
        else:
            asignados += 1
            i += 1
            j += 1
    print(asignados)


main()
