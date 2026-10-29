// C - Asignación de Habitaciones: procesar clientes por día de llegada y reutilizar la habitación
// que se libera antes (min-heap por día de salida). La cantidad de habitaciones abiertas es el mínimo.
import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        Lector in = new Lector(System.in);
        int n = in.nextInt();
        long[] a = new long[n], b = new long[n];
        long[] orden = new long[n];
        for (int i = 0; i < n; i++) {
            a[i] = in.nextLong();
            b[i] = in.nextLong();
            orden[i] = (a[i] << 18) | i;   // ordenar por llegada guardando el índice en los bits bajos
        }
        Arrays.sort(orden);
        int[] hab = new int[n];
        // Cada elemento es (día de salida << 18) | habitación: el menor día de salida queda arriba.
        long[] heap = new long[n];
        int tam = 0, k = 0;
        for (long o : orden) {
            int i = (int) (o & ((1 << 18) - 1));
            if (tam > 0 && (heap[0] >> 18) < a[i]) {   // se liberó estrictamente antes
                hab[i] = (int) (heap[0] & ((1 << 18) - 1));
                heap[0] = (b[i] << 18) | hab[i];
                bajar(heap, tam, 0);
            } else {
                hab[i] = ++k;
                heap[tam] = (b[i] << 18) | hab[i];
                subir(heap, tam++);
            }
        }
        StringBuilder sb = new StringBuilder();
        sb.append(k).append('\n');
        for (int i = 0; i < n; i++) sb.append(hab[i]).append(i + 1 < n ? ' ' : '\n');
        System.out.print(sb);
    }

    static void subir(long[] h, int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (h[p] <= h[i]) break;
            long t = h[p]; h[p] = h[i]; h[i] = t;
            i = p;
        }
    }

    static void bajar(long[] h, int tam, int i) {
        while (true) {
            int l = 2 * i + 1, r = l + 1, m = i;
            if (l < tam && h[l] < h[m]) m = l;
            if (r < tam && h[r] < h[m]) m = r;
            if (m == i) break;
            long t = h[m]; h[m] = h[i]; h[i] = t;
            i = m;
        }
    }

    // Lectura rápida de enteros (Scanner es demasiado lento para 4·10^5 números).
    static class Lector {
        private final DataInputStream in;
        private final byte[] buf = new byte[1 << 16];
        private int len = 0, ptr = 0;

        Lector(InputStream is) { in = new DataInputStream(is); }

        private int read() throws IOException {
            if (ptr == len) { len = in.read(buf, 0, buf.length); ptr = 0; if (len <= 0) return -1; }
            return buf[ptr++];
        }

        long nextLong() throws IOException {
            int c = read();
            while (c != '-' && (c < '0' || c > '9')) c = read();
            boolean neg = c == '-';
            if (neg) c = read();
            long r = 0;
            while (c >= '0' && c <= '9') { r = r * 10 + (c - '0'); c = read(); }
            return neg ? -r : r;
        }

        int nextInt() throws IOException { return (int) nextLong(); }
    }
}
