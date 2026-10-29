// El juez compila sin optimizaciones (g++ sin -O2); esta línea le pide a GCC que optimice igual.
#pragma GCC optimize("O2")
// G - Juntando Datos. Idea:
//  1) Conjuntos de un solo punto repetido: (v, v) si hay un único valor, o (a, b) y (b, a) si hay dos
//     valores con N/2 copias cada uno. Están sobre infinitas rectas, así que se cuentan aparte.
//  2) Rectas verticales x = c y horizontales y = c: posibles si c aparece al menos N/2 veces
//     (el resto de los valores forma la otra coordenada); cada una aporta exactamente un conjunto.
//  3) Rectas oblicuas q·y = p·x + r. El valor mínimo s y el máximo t aparecen en algún punto, así que la
//     recta pasa por un punto que contiene a s y otro que contiene a t: se prueban todas esas rectas
//     (y, si un único punto contiene a s y a t, las que pasan por ese punto y uno con el siguiente valor).
//     Para una recta fija, x -> y = (p·x + r) / q es inyectiva: los valores forman cadenas y ciclos
//     (los ciclos solo existen con pendiente ±1). En una cadena la cantidad de cada punto queda forzada;
//     en un ciclo de dos valores a <-> b con M copias cada uno hay M + 1 maneras de repartirlos.
// Cada conjunto con dos o más puntos distintos determina una única recta, así que no se cuenta dos veces.
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
const int OFF = 10000, RANGO = 20001;

int cnt[RANGO], suc[RANGO];
bool tieneSuc[RANGO], tienePre[RANGO], visto[RANGO];
vector<int> D;
vector<pair<int, int>> unicos;

bool existe(long long v) { return v >= -OFF && v <= OFF && cnt[v + OFF] > 0; }

// Recta oblicua por (x1, y1) y (x2, y2) como q·y = p·x + r con gcd(p, q) = 1 y q > 0, codificada en un
// único entero para poder ordenarlas y quitar repetidas. Devuelve -1 si la recta es vertical u horizontal.
long long recta(int x1, int y1, int x2, int y2) {
    long long dx = x2 - x1, dy = y2 - y1;
    if (dx == 0 || dy == 0) return -1;
    long long g = __gcd(llabs(dx), llabs(dy)), p = dy / g, q = dx / g;
    if (q < 0) { p = -p; q = -q; }
    long long r = q * y1 - p * x1;                                  // |r| <= 4·10^8
    return ((p + 20000) * 20001 + q) * 800000001LL + (r + 400000000);
}

long long contarEnRecta(long long clave) {
    long long r = clave % 800000001LL - 400000000, t = clave / 800000001LL;
    long long q = t % 20001, p = t / 20001 - 20000;
    // Descarte rápido: todo valor debe poder ser la x o la y de algún punto de la recta.
    for (int v : D) {
        long long num = p * v + r;
        if (num % q == 0 && existe(num / q)) continue;
        num = q * v - r;
        if (num % p == 0 && existe(num / p)) continue;
        return 0;
    }
    for (int v : D) tieneSuc[v + OFF] = tienePre[v + OFF] = visto[v + OFF] = false;
    for (int x : D) {
        long long num = p * x + r;
        if (num % q == 0 && existe(num / q)) {
            int y = num / q;
            tieneSuc[x + OFF] = true;
            suc[x + OFF] = y;
            tienePre[y + OFF] = true;
        }
    }
    long long formas = 1;
    for (int v0 : D) {                                              // cadenas
        if (tienePre[v0 + OFF]) continue;
        int v = v0, entrantes = 0;
        while (true) {
            visto[v + OFF] = true;
            int salientes = cnt[v + OFF] - entrantes;               // puntos (v, suc[v]) forzados
            if (salientes < 0) return 0;
            if (!tieneSuc[v + OFF]) {
                if (salientes != 0) return 0;
                break;
            }
            v = suc[v + OFF];
            entrantes = salientes;
        }
    }
    for (int v : D) {                                               // ciclos
        if (visto[v + OFF]) continue;
        int u = suc[v + OFF];
        visto[v + OFF] = visto[u + OFF] = true;
        if (u == v) {                                               // punto (v, v): usa dos copias
            if (cnt[v + OFF] % 2) return 0;
        } else {                                                    // v <-> u
            if (cnt[v + OFF] != cnt[u + OFF]) return 0;
            formas = formas * (cnt[v + OFF] + 1) % MOD;
        }
    }
    // Los conjuntos de un solo punto que están sobre esta recta ya se contaron aparte.
    for (auto &ab : unicos)
        if (tieneSuc[ab.first + OFF] && suc[ab.first + OFF] == ab.second) formas = (formas - 1 + MOD) % MOD;
    return formas;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        if (cnt[v + OFF]++ == 0) D.push_back(v);
    }
    sort(D.begin(), D.end());
    int h = n / 2, d = D.size();
    auto c = [&](int v) { return cnt[v + OFF]; };
    if (d == 1) unicos = {{D[0], D[0]}};
    else if (d == 2 && c(D[0]) == h && c(D[1]) == h) unicos = {{D[0], D[1]}, {D[1], D[0]}};
    long long total = unicos.size();
    for (int v : D)                                                 // verticales y horizontales
        if (c(v) >= h && d - (c(v) == h ? 1 : 0) >= 2) total += 2;

    int s = D.front(), t = D.back();
    vector<pair<int, int>> conS, conT;
    for (int u : D) {
        conS.push_back({s, u}); conS.push_back({u, s});
        conT.push_back({t, u}); conT.push_back({u, t});
    }
    vector<long long> rectas;
    for (auto &P : conS)
        for (auto &Q : conT) {
            long long L = recta(P.first, P.second, Q.first, Q.second);
            if (L >= 0) rectas.push_back(L);
        }
    if (s != t && c(s) == c(t)) {                                   // quizá un único punto contiene a s y a t
        int s2 = INT_MAX;
        for (int v : D) if (v != s && v != t) { s2 = v; break; }
        if (s2 != INT_MAX) {
            pair<int, int> R[2] = {{s, t}, {t, s}};
            for (auto &P : R)
                for (int u : D) {
                    long long L1 = recta(P.first, P.second, s2, u), L2 = recta(P.first, P.second, u, s2);
                    if (L1 >= 0) rectas.push_back(L1);
                    if (L2 >= 0) rectas.push_back(L2);
                }
        }
    }
    sort(rectas.begin(), rectas.end());
    rectas.erase(unique(rectas.begin(), rectas.end()), rectas.end());
    for (long long L : rectas) total = (total + contarEnRecta(L)) % MOD;
    cout << total % MOD << '\n';
}
