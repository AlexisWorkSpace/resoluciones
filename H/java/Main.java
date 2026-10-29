// H - Números de Fibonacci: "fast doubling", O(log n).
//   F(2k)   = F(k) · (2·F(k+1) − F(k))
//   F(2k+1) = F(k)^2 + F(k+1)^2
import java.util.*;

public class Main {
    static final long MOD = 1_000_000_007L;

    // Devuelve {F(n), F(n+1)} módulo MOD.
    static long[] fib(long n) {
        if (n == 0) return new long[]{0, 1};
        long[] r = fib(n >> 1);
        long a = r[0], b = r[1];
        long c = a * ((2 * b - a + MOD) % MOD) % MOD;
        long d = (a * a + b * b) % MOD;
        return (n & 1) == 1 ? new long[]{d, (c + d) % MOD} : new long[]{c, d};
    }

    public static void main(String[] args) {
        long n = new Scanner(System.in).nextLong();
        System.out.println(fib(n)[0]);
    }
}
