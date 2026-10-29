// B - Combinaciones de Monedas II: DP de "mochila no acotada" que cuenta combinaciones sin orden.
// dp[s] = formas de formar s con las monedas procesadas; recorrer las monedas en el ciclo externo
// hace que cada combinación se cuente una sola vez. O(n·x).
import java.io.*;

public class Main {
    static final int MOD = 1_000_000_007;

    public static void main(String[] args) throws IOException {
        StreamTokenizer st = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
        st.nextToken(); int n = (int) st.nval;
        st.nextToken(); int x = (int) st.nval;
        int[] c = new int[n];
        for (int i = 0; i < n; i++) { st.nextToken(); c[i] = (int) st.nval; }
        int[] dp = new int[x + 1];
        dp[0] = 1;
        for (int v : c)
            for (int s = v; s <= x; s++) {
                int t = dp[s] + dp[s - v];
                dp[s] = t >= MOD ? t - MOD : t;
            }
        System.out.println(dp[x]);
    }
}
