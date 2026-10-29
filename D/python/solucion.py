# D - Algoritmo Extraño: simulación directa (los valores intermedios superan 2^31; en Python no importa).
n = int(input())
valores = [n]
while n != 1:
    n = n // 2 if n % 2 == 0 else 3 * n + 1
    valores.append(n)
print(" ".join(map(str, valores)))
