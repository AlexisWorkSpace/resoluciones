# C - Asignación de Habitaciones: procesar clientes por día de llegada y reutilizar la habitación
# que se libera antes (min-heap por día de salida). La cantidad de habitaciones abiertas es el mínimo.
# Cada entrada del heap es salida * 2^18 + habitacion (un solo entero: más rápido que tuplas).
import sys
from heapq import heappush, heapreplace

DESPL = 1 << 18  # n <= 2·10^5 < 2^18


def main():
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    llegada = list(map(int, data[1:2 * n + 1:2]))
    salida = list(map(int, data[2:2 * n + 2:2]))
    orden = sorted(range(n), key=llegada.__getitem__)
    habitacion = [0] * n
    heap = []
    k = 0
    for i in orden:
        if heap and heap[0] // DESPL < llegada[i]:   # se liberó estrictamente antes de que llegue
            h = heap[0] % DESPL
            heapreplace(heap, salida[i] * DESPL + h)
        else:
            k += 1
            h = k
            heappush(heap, salida[i] * DESPL + h)
        habitacion[i] = h
    sys.stdout.write(f"{k}\n{' '.join(map(str, habitacion))}\n")


main()
