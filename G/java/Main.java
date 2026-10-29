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
import java.io.*;
import java.util.*;

public class Main {
    static final long MOD = 1_000_000_007L;
    static final int OFF = 10000, RANGO = 20001;

    static int[] cnt = new int[RANGO], suc = new int[RANGO];
    static boolean[] tieneSuc = new boolean[RANGO], tienePre = new boolean[RANGO], visto = new boolean[RANGO];
    static int[] D;
    static int[][] unicos = new int[0][];
    static long[] rectas = new long[200000];
    static int nRectas = 0;

    static boolean existe(long v) { return v >= -OFF && v <= OFF && cnt[(int) v + OFF] > 0; }

    static long mcd(long a, long b) { return b == 0 ? a : mcd(b, a % b); }

    // Recta oblicua por (x1, y1) y (x2, y2) como q·y = p·x + r con gcd(p, q) = 1 y q > 0, codificada en un
    // único long para poder ordenarlas y quitar repetidas. Las verticales y horizontales se ignoran.
    static void agregarRecta(int x1, int y1, int x2, int y2) {
        long dx = x2 - x1, dy = y2 - y1;
        if (dx == 0 || dy == 0) return;
        long g = mcd(Math.abs(dx), Math.abs(dy)), p = dy / g, q = dx / g;
        if (q < 0) { p = -p; q = -q; }
        long r = q * y1 - p * x1;                                    // |r| <= 4·10^8
        rectas[nRectas++] = ((p + 20000) * 20001 + q) * 800000001L + (r + 400000000);
    }

    static long contarEnRecta(long clave) {
        long r = clave % 800000001L - 400000000, t = clave / 800000001L;
        long q = t % 20001, p = t / 20001 - 20000;
        // Descarte rápido: todo valor debe poder ser la x o la y de algún punto de la recta.
        for (int v : D) {
            long num = p * v + r;
            if (num % q == 0 && existe(num / q)) continue;
            num = q * v - r;
            if (num % p == 0 && existe(num / p)) continue;
            return 0;
        }
        for (int v : D) tieneSuc[v + OFF] = tienePre[v + OFF] = visto[v + OFF] = false;
        for (int x : D) {
            long num = p * x + r;
            if (num % q == 0 && existe(num / q)) {
                int y = (int) (num / q);
                tieneSuc[x + OFF] = true;
                suc[x + OFF] = y;
                tienePre[y + OFF] = true;
            }
        }
        long formas = 1;
        for (int v0 : D) {                                           // cadenas
            if (tienePre[v0 + OFF]) continue;
            int v = v0, entrantes = 0;
            while (true) {
                visto[v + OFF] = true;
                int salientes = cnt[v + OFF] - entrantes;            // puntos (v, suc[v]) forzados
                if (salientes < 0) return 0;
                if (!tieneSuc[v + OFF]) {
                    if (salientes != 0) return 0;
                    break;
                }
                v = suc[v + OFF];
                entrantes = salientes;
            }
        }
        for (int v : D) {                                            // ciclos
            if (visto[v + OFF]) continue;
            int u = suc[v + OFF];
            visto[v + OFF] = visto[u + OFF] = true;
            if (u == v) {                                            // punto (v, v): usa dos copias
                if (cnt[v + OFF] % 2 != 0) return 0;
            } else {                                                 // v <-> u
                if (cnt[v + OFF] != cnt[u + OFF]) return 0;
                formas = formas * (cnt[v + OFF] + 1) % MOD;
            }
        }
        // Los conjuntos de un solo punto que están sobre esta recta ya se contaron aparte.
        for (int[] ab : unicos)
            if (tieneSuc[ab[0] + OFF] && suc[ab[0] + OFF] == ab[1]) formas = (formas - 1 + MOD) % MOD;
        return formas;
    }

    public static void main(String[] args) throws IOException {
        StringTokenizer st = new StringTokenizer(new String(System.in.readAllBytes()));
        int n = Integer.parseInt(st.nextToken());
        TreeSet<Integer> distintos = new TreeSet<>();
        for (int i = 0; i < n; i++) {
            int v = Integer.parseInt(st.nextToken());
            cnt[v + OFF]++;
            distintos.add(v);
        }
        D = distintos.stream().mapToInt(Integer::intValue).toArray();
        int h = n / 2, d = D.length;
        if (d == 1) unicos = new int[][]{{D[0], D[0]}};
        else if (d == 2 && cnt[D[0] + OFF] == h && cnt[D[1] + OFF] == h) unicos = new int[][]{{D[0], D[1]}, {D[1], D[0]}};
        long total = unicos.length;
        for (int v : D) {                                            // verticales y horizontales
            int c = cnt[v + OFF];
            if (c >= h && d - (c == h ? 1 : 0) >= 2) total += 2;
        }

        int s = D[0], t = D[d - 1];
        for (int u : D) {
            int[][] conS = {{s, u}, {u, s}};
            for (int w : D) {
                int[][] conT = {{t, w}, {w, t}};
                for (int[] P : conS)
                    for (int[] Q : conT) agregarRecta(P[0], P[1], Q[0], Q[1]);
            }
        }
        if (s != t && cnt[s + OFF] == cnt[t + OFF] && d > 2) {      // quizá un único punto contiene a s y a t
            int s2 = D[1];
            int[][] R = {{s, t}, {t, s}};
            for (int[] P : R)
                for (int u : D) {
                    agregarRecta(P[0], P[1], s2, u);
                    agregarRecta(P[0], P[1], u, s2);
                }
        }
        long[] unicas = Arrays.stream(rectas, 0, nRectas).sorted().distinct().toArray();
        for (long L : unicas) total = (total + contarEnRecta(L)) % MOD;
        System.out.println(total % MOD);
    }
}
