// E - Viajes en Ascensor: DP sobre subconjuntos. Para cada conjunto de personas ya subidas,
// dp[mask] = (mínimo de viajes, menor peso en el último viaje). O(2^n · n).
import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        StringTokenizer st = new StringTokenizer(new String(System.in.readAllBytes()));
        int n = Integer.parseInt(st.nextToken());
        long x = Long.parseLong(st.nextToken());
        long[] w = new long[n];
        for (int i = 0; i < n; i++) w[i] = Long.parseLong(st.nextToken());
        int total = 1 << n;
        int[] viajes = new int[total];
        long[] ultimo = new long[total];
        viajes[0] = 1;
        for (int mask = 1; mask < total; mask++) {
            int mejorV = n + 1;
            long mejorU = 0;
            for (int i = 0; i < n; i++) {
                if ((mask >> i & 1) == 0) continue;
                int prev = mask ^ (1 << i);
                int v = viajes[prev];
                long u = ultimo[prev];
                if (u + w[i] <= x) u += w[i];
                else { v++; u = w[i]; }
                if (v < mejorV || (v == mejorV && u < mejorU)) { mejorV = v; mejorU = u; }
            }
            viajes[mask] = mejorV;
            ultimo[mask] = mejorU;
        }
        System.out.println(viajes[total - 1]);
    }
}
