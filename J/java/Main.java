// J - Número de cadenas: s[i..i+2] es palíndromo  <=>  s[i] == s[i+2].
// Las posiciones pares y las impares forman dos cadenas independientes; entre las dos tienen N - 2 pares
// (s[i], s[i+2]) y cada uno puede ser "igual" o "distinto". Elegir cuáles K son iguales: C(N-2, K).
// El primer carácter de cada cadena tiene A opciones, cada par igual 1 y cada par distinto A - 1:
//     respuesta = A^2 · (A-1)^(N-2-K) · C(N-2, K)          (N >= 2)
// Con N = 1 no hay subcadenas de largo 3: la respuesta es A si K = 0 y 0 si no.
import java.util.*;

public class Main {
    static final long MOD = 998244353L;

    static long potencia(long b, long e) {
        long r = 1;
        b %= MOD;
        for (; e > 0; e >>= 1, b = b * b % MOD)
            if ((e & 1) == 1) r = r * b % MOD;
        return r;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        long n = sc.nextLong(), k = sc.nextLong(), a = sc.nextLong();
        if (n == 1) { System.out.println(k == 0 ? a : 0); return; }
        if (k > n - 2) { System.out.println(0); return; }
        long m = n - 2, r = Math.min(k, m - k), num = 1, den = 1;
        for (long i = 0; i < r; i++) {
            num = num * ((m - i) % MOD) % MOD;
            den = den * (i + 1) % MOD;
        }
        long binom = num * potencia(den, MOD - 2) % MOD;
        System.out.println(a * a % MOD * potencia(a - 1, m - k) % MOD * binom % MOD);
    }
}
