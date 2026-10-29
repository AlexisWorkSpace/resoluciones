// H - Números de Fibonacci: "fast doubling", O(log n).
//   F(2k)   = F(k) · (2·F(k+1) − F(k))
//   F(2k+1) = F(k)^2 + F(k+1)^2
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

// Devuelve (F(n), F(n+1)) módulo MOD.
pair<long long, long long> fib(long long n) {
    if (n == 0) return {0, 1};
    pair<long long, long long> ab = fib(n >> 1);
    long long a = ab.first, b = ab.second;
    long long c = a * ((2 * b - a + MOD) % MOD) % MOD;
    long long d = (a * a + b * b) % MOD;
    if (n & 1) return {d, (c + d) % MOD};
    return {c, d};
}

int main() {
    long long n;
    cin >> n;
    cout << fib(n).first << '\n';
}
