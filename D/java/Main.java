// D - Algoritmo Extraño: simulación directa. Se usa long porque los valores intermedios superan 2^31.
import java.util.*;

public class Main {
    public static void main(String[] args) {
        long n = new Scanner(System.in).nextLong();
        StringBuilder sb = new StringBuilder().append(n);
        while (n != 1) {
            n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
            sb.append(' ').append(n);
        }
        System.out.println(sb);
    }
}
