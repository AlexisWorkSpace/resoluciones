/* El juez compila sin optimizaciones (gcc sin -O2); esta línea le pide a GCC que optimice igual. */
#pragma GCC optimize("O2")
/* C - Asignación de Habitaciones: procesar clientes por día de llegada y reutilizar la habitación
   que se libera antes (min-heap por día de salida). La cantidad de habitaciones abiertas es el mínimo. */
#include <stdio.h>
#include <stdlib.h>

typedef struct { int llegada, salida, id; } Cliente;
typedef struct { int salida, hab; } Nodo;

static Nodo heap[200005];
static int tam = 0;

static void subir(int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].salida <= heap[i].salida) break;
        Nodo t = heap[p]; heap[p] = heap[i]; heap[i] = t;
        i = p;
    }
}

static void bajar(int i) {
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < tam && heap[l].salida < heap[m].salida) m = l;
        if (r < tam && heap[r].salida < heap[m].salida) m = r;
        if (m == i) break;
        Nodo t = heap[m]; heap[m] = heap[i]; heap[i] = t;
        i = m;
    }
}

static int cmp(const void *x, const void *y) {
    const Cliente *a = x, *b = y;
    return (a->llegada > b->llegada) - (a->llegada < b->llegada);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    Cliente *c = malloc(sizeof(Cliente) * n);
    int *hab = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) { scanf("%d %d", &c[i].llegada, &c[i].salida); c[i].id = i; }
    qsort(c, n, sizeof(Cliente), cmp);
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (tam > 0 && heap[0].salida < c[i].llegada) {   /* se liberó estrictamente antes */
            hab[c[i].id] = heap[0].hab;
            heap[0].salida = c[i].salida;
            bajar(0);
        } else {
            hab[c[i].id] = ++k;
            heap[tam].salida = c[i].salida;
            heap[tam].hab = k;
            subir(tam++);
        }
    }
    printf("%d\n", k);
    for (int i = 0; i < n; i++) printf("%d%c", hab[i], i + 1 < n ? ' ' : '\n');
    return 0;
}
