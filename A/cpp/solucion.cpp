// El juez compila sin optimizaciones (g++ sin -O2); esta línea le pide a GCC que optimice igual.
#pragma GCC optimize("O2")
// A - Apartamentos: ordenar ambas listas y emparejar con dos punteros (greedy).
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    long long k;
    scanf("%d %d %lld", &n, &m, &k);   // scanf: la entrada tiene hasta 4·10^5 números
    vector<long long> a(n), b(m);
    for (auto &v : a) scanf("%lld", &v);
    for (auto &v : b) scanf("%lld", &v);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int i = 0, j = 0, asignados = 0;
    while (i < n && j < m) {
        if (b[j] < a[i] - k) j++;
        else if (b[j] > a[i] + k) i++;
        else { asignados++; i++; j++; }
    }
    printf("%d\n", asignados);
}
