// A - Apartamentos: ordenar ambas listas y emparejar con dos punteros (greedy).
import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        Lector in = new Lector(System.in);
        int n = in.nextInt(), m = in.nextInt();
        long k = in.nextLong();
        long[] a = new long[n], b = new long[m];
        for (int i = 0; i < n; i++) a[i] = in.nextLong();
        for (int j = 0; j < m; j++) b[j] = in.nextLong();
        Arrays.sort(a);
        Arrays.sort(b);
        int i = 0, j = 0, asignados = 0;
        while (i < n && j < m) {
            if (b[j] < a[i] - k) j++;
            else if (b[j] > a[i] + k) i++;
            else { asignados++; i++; j++; }
        }
        System.out.println(asignados);
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
