// F - Hangar del SBC: respuesta = contar(B) - contar(A - 1), donde contar(T) = cantidad de formas de elegir
// K cajas con peso total <= T. Con las cajas ordenadas, contar(i, k, T) decide sobre la caja más pesada
// (i - 1): no tomarla o tomarla. Se corta antes cuando:
//   - las k cajas más pesadas disponibles ya caben -> cualquier elección cabe: C(i, k);
//   - las k más livianas no caben -> ninguna cabe: 0.
// Como cada caja pesa al menos el doble que cualquier otra más liviana, en cada paso una de las dos ramas
// termina enseguida y la recursión es casi lineal.
// Las sumas se cortan apenas superan T (T <= 2·10^18), así nunca desbordan un long.
import java.io.*;
import java.util.*;

public class Main {
    static long[] p;
    static long[][] C = new long[51][51];

    public static void main(String[] args) throws IOException {
        StringTokenizer st = new StringTokenizer(new String(System.in.readAllBytes()));
        int n = Integer.parseInt(st.nextToken()), k = Integer.parseInt(st.nextToken());
        p = new long[n];
        for (int i = 0; i < n; i++) p[i] = Long.parseLong(st.nextToken());
        long a = Long.parseLong(st.nextToken()), b = Long.parseLong(st.nextToken());
        Arrays.sort(p);
        for (int i = 0; i <= 50; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++) C[i][j] = C[i - 1][j - 1] + (j < i ? C[i - 1][j] : 0);
        }
        System.out.println(contar(n, k, b) - contar(n, k, a - 1));
    }

    static boolean cabe(int desde, int hasta, long t) {
        long s = 0;
        for (int j = desde; j < hasta; j++) {
            s += p[j];
            if (s > t) return false;
        }
        return true;
    }

    static long contar(int i, int k, long t) {
        if (k < 0 || t < 0 || i < k) return 0;
        if (k == 0) return 1;
        if (cabe(i - k, i, t)) return C[i][k];
        if (!cabe(0, k, t)) return 0;
        long r = contar(i - 1, k, t);
        if (t >= p[i - 1]) r += contar(i - 1, k - 1, t - p[i - 1]);
        return r;
    }
}
