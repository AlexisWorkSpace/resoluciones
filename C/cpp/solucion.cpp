// El juez compila sin optimizaciones (g++ sin -O2); esta línea le pide a GCC que optimice igual.
#pragma GCC optimize("O2")
// C - Asignación de Habitaciones: procesar clientes por día de llegada y reutilizar la habitación
// que se libera antes (min-heap por día de salida). La cantidad de habitaciones abiertas es el mínimo.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);   // scanf/printf: entrada y salida grandes (4·10^5 y 2·10^5 números)
    vector<int> a(n), b(n), orden(n), hab(n);
    for (int i = 0; i < n; i++) scanf("%d %d", &a[i], &b[i]);
    iota(orden.begin(), orden.end(), 0);
    sort(orden.begin(), orden.end(), [&](int x, int y) { return a[x] < a[y]; });
    // (día de salida, habitación), el menor día de salida arriba
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    int k = 0;
    for (int i : orden) {
        if (!pq.empty() && pq.top().first < a[i]) {   // se liberó estrictamente antes
            hab[i] = pq.top().second;
            pq.pop();
        } else {
            hab[i] = ++k;
        }
        pq.push({b[i], hab[i]});
    }
    printf("%d\n", k);
    for (int i = 0; i < n; i++) printf("%d%c", hab[i], i + 1 < n ? ' ' : '\n');
}
