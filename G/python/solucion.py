# G - Juntando Datos. Idea:
#  1) Conjuntos de un solo punto repetido: (v, v) si hay un único valor, o (a, b) y (b, a) si hay dos
#     valores con N/2 copias cada uno. Están sobre infinitas rectas, así que se cuentan aparte.
#  2) Rectas verticales x = c y horizontales y = c: posibles si c aparece al menos N/2 veces
#     (el resto de los valores forma la otra coordenada); cada una aporta exactamente un conjunto.
#  3) Rectas oblicuas q·y = p·x + r. El valor mínimo s y el máximo t aparecen en algún punto, así que la
#     recta pasa por un punto que contiene a s y otro que contiene a t: se prueban todas esas rectas
#     (y, si un único punto contiene a s y a t, las que pasan por ese punto y uno con el siguiente valor).
#     Para una recta fija, x -> y = (p·x + r) / q es inyectiva: los valores forman cadenas y ciclos
#     (los ciclos solo existen con pendiente ±1). En una cadena la cantidad de cada punto queda forzada;
#     en un ciclo de dos valores a <-> b con M copias cada uno hay M + 1 maneras de repartirlos.
# Cada conjunto con dos o más puntos distintos determina una única recta, así que no se cuenta dos veces.
import sys
from collections import Counter
from math import gcd

MOD = 10**9 + 7


def recta(P, Q):
    """Recta oblicua por P y Q como (p, q, r) con q·y = p·x + r, gcd(p, q) = 1 y q > 0; None si es eje."""
    (x1, y1), (x2, y2) = P, Q
    dx, dy = x2 - x1, y2 - y1
    if dx == 0 or dy == 0:
        return None
    g = gcd(abs(dx), abs(dy))
    p, q = dy // g, dx // g
    if q < 0:
        p, q = -p, -q
    return p, q, q * y1 - p * x1


def contar_en_recta(cnt, D, linea, unicos):
    p, q, r = linea
    # Descarte rápido: todo valor debe poder ser la x o la y de algún punto de la recta.
    for v in D:
        num = p * v + r
        if num % q == 0 and num // q in cnt:
            continue
        num = q * v - r
        if num % p == 0 and num // p in cnt:
            continue
        return 0
    suc, pre = {}, {}
    for x in D:
        num = p * x + r
        if num % q == 0 and num // q in cnt:
            suc[x] = num // q
            pre[num // q] = x
    formas = 1
    vistos = set()
    for v0 in D:                              # cadenas: empiezan en un valor sin predecesor
        if v0 in pre:
            continue
        v, entrantes = v0, 0
        while True:
            vistos.add(v)
            salientes = cnt[v] - entrantes    # puntos (v, suc[v]) forzados
            if salientes < 0:
                return 0
            if v not in suc:
                if salientes != 0:
                    return 0
                break
            v, entrantes = suc[v], salientes
    for v in D:                               # ciclos
        if v in vistos:
            continue
        u = suc[v]
        vistos.add(v)
        vistos.add(u)
        if u == v:                            # punto (v, v): usa dos copias
            if cnt[v] % 2:
                return 0
        else:                                 # v <-> u
            if cnt[v] != cnt[u]:
                return 0
            formas = formas * (cnt[v] + 1) % MOD
    # Los conjuntos de un solo punto que están sobre esta recta ya se contaron en el paso 1.
    for a, b in unicos:
        if suc.get(a) == b:
            formas -= 1
    return formas


def rectas_candidatas(cnt, D):
    s, t = D[0], D[-1]
    con_s = [(s, u) for u in D] + [(u, s) for u in D]
    con_t = [(t, u) for u in D] + [(u, t) for u in D]
    rectas = set()
    for P in con_s:
        for Q in con_t:
            L = recta(P, Q)
            if L:
                rectas.add(L)
    if s != t and cnt[s] == cnt[t]:           # quizá un único punto contiene a s y a t
        resto = cnt.copy()
        resto[s] -= cnt[s]
        resto[t] -= cnt[t]
        quedan = sorted(v for v in resto if resto[v] > 0)
        if quedan:
            s2 = quedan[0]
            for R in ((s, t), (t, s)):
                for u in D:
                    for R2 in ((s2, u), (u, s2)):
                        L = recta(R, R2)
                        if L:
                            rectas.add(L)
    return rectas


def main():
    data = sys.stdin.read().split()
    n = int(data[0])
    vals = list(map(int, data[1:1 + n]))
    h = n // 2
    cnt = Counter(vals)
    D = sorted(cnt)
    if len(D) == 1:
        unicos = [(D[0], D[0])]
    elif len(D) == 2 and cnt[D[0]] == h and cnt[D[1]] == h:
        unicos = [(D[0], D[1]), (D[1], D[0])]
    else:
        unicos = []
    total = len(unicos)
    for c in D:                               # verticales y horizontales
        if cnt[c] >= h and len(D) - (1 if cnt[c] == h else 0) >= 2:
            total += 2
    for L in rectas_candidatas(cnt, D):
        total += contar_en_recta(cnt, D, L, unicos)
    print(total % MOD)


main()
