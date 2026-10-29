# Resoluciones — Tecla-Ton, Primera Edición

Resoluciones de los ejercicios A–J y del ejercicio de práctica T, en cuatro lenguajes.

```
<ejercicio>/
  c/solucion.c
  cpp/solucion.cpp
  java/Main.java
  python/solucion.py
```

Cada archivo empieza con un comentario que explica la idea de la solución.

## Cómo se probaron

Todas se corrieron contra los casos de prueba del juez (entre 32 y 50 casos por ejercicio), con la misma forma
de compilar y ejecutar que usa el juez:

| Lenguaje | Comando |
|----------|---------|
| C        | `gcc -o app solucion.c` |
| C++      | `g++ -o app solucion.cpp` |
| Java 17  | `javac Main.java && java Main` (la clase debe llamarse `Main`) |
| Python 3.10 | `python3 solucion.py` |

El juez compila **sin `-O2`**. Por eso las soluciones de C y C++ más pesadas (A, B, C, E, G) empiezan con
`#pragma GCC optimize("O2")`, que le pide a GCC que optimice igual.

## Límites conocidos de Python

Con 1 s de límite, Python no alcanza en los casos más grandes de dos ejercicios. La idea es la misma, pero el
intérprete es demasiado lento para esa cantidad de operaciones:

- **B**: la DP hace hasta 10^8 operaciones (100 monedas × x = 10^6).
- **E**: la DP sobre subconjuntos hace unas 2·10^7 operaciones con n = 20.
