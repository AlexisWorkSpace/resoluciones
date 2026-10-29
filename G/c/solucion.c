/* El juez compila sin optimizaciones (gcc sin -O2); esta línea le pide a GCC que optimice igual. */
#pragma GCC optimize("O2")
/* G - Juntando Datos. Idea:
    1) Conjuntos de un solo punto repetido: (v, v) si hay un único valor, o (a, b) y (b, a) si hay dos
       valores con N/2 copias cada uno. Están sobre infinitas rectas, así que se cuentan aparte.
    2) Rectas verticales x = c y horizontales y = c: posibles si c aparece al menos N/2 veces
       (el resto de los valores forma la otra coordenada); cada una aporta exactamente un conjunto.
    3) Rectas oblicuas q·y = p·x + r. El valor mínimo s y el máximo t aparecen en algún punto, así que la
       recta pasa por un punto que contiene a s y otro que contiene a t: se prueban todas esas rectas
       (y, si un único punto contiene a s y a t, las que pasan por ese punto y uno con el siguiente valor).
       Para una recta fija, x -> y = (p·x + r) / q es inyectiva: los valores forman cadenas y ciclos
       (los ciclos solo existen con pendiente ±1). En una cadena la cantidad de cada punto queda forzada;
       en un ciclo de dos valores a <-> b con M copias cada uno hay M + 1 maneras de repartirlos.
   Cada conjunto con dos o más puntos distintos determina una única recta, así que no se cuenta dos veces. */
#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007LL
#define OFF 10000
#define RANGO 20001

static int cnt[RANGO], suc[RANGO], tieneSuc[RANGO], tienePre[RANGO], visto[RANGO];
static int D[200], d = 0;
static int unicos[2][2], nUnicos = 0;
static long long rectas[200000];
static int nRectas = 0;

static int existe(long long v) { return v >= -OFF && v <= OFF && cnt[v + OFF] > 0; }

static long long mcd(long long a, long long b) { return b ? mcd(b, a % b) : a; }

/* Recta oblicua por (x1, y1) y (x2, y2) como q·y = p·x + r con gcd(p, q) = 1 y q > 0, codificada en un
   único entero para poder ordenarlas y quitar repetidas. Las verticales y horizontales se ignoran. */
static void agregarRecta(int x1, int y1, int x2, int y2) {
    long long dx = x2 - x1, dy = y2 - y1;
    if (dx == 0 || dy == 0) return;
    long long g = mcd(llabs(dx), llabs(dy)), p = dy / g, q = dx / g;
    if (q < 0) { p = -p; q = -q; }
    long long r = q * y1 - p * x1;                                   /* |r| <= 4·10^8 */
    rectas[nRectas++] = ((p + 20000) * 20001 + q) * 800000001LL + (r + 400000000);
}

static long long contarEnRecta(long long clave) {
    long long r = clave % 800000001LL - 400000000, t = clave / 800000001LL;
    long long q = t % 20001, p = t / 20001 - 20000;
    /* Descarte rápido: todo valor debe poder ser la x o la y de algún punto de la recta. */
    for (int i = 0; i < d; i++) {
        long long v = D[i], num = p * v + r;
        if (num % q == 0 && existe(num / q)) continue;
        num = q * v - r;
        if (num % p == 0 && existe(num / p)) continue;
        return 0;
    }
    for (int i = 0; i < d; i++) tieneSuc[D[i] + OFF] = tienePre[D[i] + OFF] = visto[D[i] + OFF] = 0;
    for (int i = 0; i < d; i++) {
        long long num = p * D[i] + r;
        if (num % q == 0 && existe(num / q)) {
            int y = (int)(num / q);
            tieneSuc[D[i] + OFF] = 1;
            suc[D[i] + OFF] = y;
            tienePre[y + OFF] = 1;
        }
    }
    long long formas = 1;
    for (int i = 0; i < d; i++) {                                    /* cadenas */
        if (tienePre[D[i] + OFF]) continue;
        int v = D[i], entrantes = 0;
        for (;;) {
            visto[v + OFF] = 1;
            int salientes = cnt[v + OFF] - entrantes;                /* puntos (v, suc[v]) forzados */
            if (salientes < 0) return 0;
            if (!tieneSuc[v + OFF]) {
                if (salientes != 0) return 0;
                break;
            }
            v = suc[v + OFF];
            entrantes = salientes;
        }
    }
    for (int i = 0; i < d; i++) {                                    /* ciclos */
        int v = D[i];
        if (visto[v + OFF]) continue;
        int u = suc[v + OFF];
        visto[v + OFF] = visto[u + OFF] = 1;
        if (u == v) {                                                /* punto (v, v): usa dos copias */
            if (cnt[v + OFF] % 2) return 0;
        } else {                                                     /* v <-> u */
            if (cnt[v + OFF] != cnt[u + OFF]) return 0;
            formas = formas * (cnt[v + OFF] + 1) % MOD;
        }
    }
    /* Los conjuntos de un solo punto que están sobre esta recta ya se contaron aparte. */
    for (int i = 0; i < nUnicos; i++)
        if (tieneSuc[unicos[i][0] + OFF] && suc[unicos[i][0] + OFF] == unicos[i][1]) formas = (formas - 1 + MOD) % MOD;
    return formas;
}

static int cmpInt(const void *x, const void *y) {
    int a = *(const int *)x, b = *(const int *)y;
    return (a > b) - (a < b);
}

static int cmpLL(const void *x, const void *y) {
    long long a = *(const long long *)x, b = *(const long long *)y;
    return (a > b) - (a < b);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        if (cnt[v + OFF]++ == 0) D[d++] = v;
    }
    qsort(D, d, sizeof(int), cmpInt);
    int h = n / 2;
    if (d == 1) {
        unicos[0][0] = unicos[0][1] = D[0];
        nUnicos = 1;
    } else if (d == 2 && cnt[D[0] + OFF] == h && cnt[D[1] + OFF] == h) {
        unicos[0][0] = D[0]; unicos[0][1] = D[1];
        unicos[1][0] = D[1]; unicos[1][1] = D[0];
        nUnicos = 2;
    }
    long long total = nUnicos;
    for (int i = 0; i < d; i++) {                                    /* verticales y horizontales */
        int c = cnt[D[i] + OFF];
        if (c >= h && d - (c == h ? 1 : 0) >= 2) total += 2;
    }

    int s = D[0], t = D[d - 1];
    for (int i = 0; i < d; i++) {
        int Ps[2][2] = {{s, D[i]}, {D[i], s}};
        for (int j = 0; j < d; j++) {
            int Qs[2][2] = {{t, D[j]}, {D[j], t}};
            for (int a = 0; a < 2; a++)
                for (int b = 0; b < 2; b++) agregarRecta(Ps[a][0], Ps[a][1], Qs[b][0], Qs[b][1]);
        }
    }
    if (s != t && cnt[s + OFF] == cnt[t + OFF] && d > 2) {          /* quizá un único punto contiene a s y a t */
        int s2 = D[1];
        int R[2][2] = {{s, t}, {t, s}};
        for (int a = 0; a < 2; a++)
            for (int i = 0; i < d; i++) {
                agregarRecta(R[a][0], R[a][1], s2, D[i]);
                agregarRecta(R[a][0], R[a][1], D[i], s2);
            }
    }
    qsort(rectas, nRectas, sizeof(long long), cmpLL);
    for (int i = 0; i < nRectas; i++)
        if (i == 0 || rectas[i] != rectas[i - 1]) total = (total + contarEnRecta(rectas[i])) % MOD;
    printf("%lld\n", total % MOD);
    return 0;
}
