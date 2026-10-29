// I - Rompiendo Rosarigasino: la transformación convierte una vocal v en "vGASv". Para deshacerla se busca
// cada posición i donde aparece v + "GAS" + v y se quitan los 4 caracteres "GASv". Las traducciones se
// guardan en un Set porque dos posiciones distintas pueden dar la misma palabra (por ejemplo AGASAGASA).
import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        String w = new BufferedReader(new InputStreamReader(System.in)).readLine().trim();
        Set<String> traducciones = new HashSet<>();
        for (int i = 0; i + 4 < w.length(); i++) {
            char v = w.charAt(i);
            if ("AEIOU".indexOf(v) >= 0 && w.startsWith("GAS", i + 1) && w.charAt(i + 4) == v)
                traducciones.add(w.substring(0, i + 1) + w.substring(i + 5));
        }
        if (traducciones.isEmpty()) System.out.println("-");
        else if (traducciones.size() == 1) System.out.println(traducciones.iterator().next());
        else System.out.println("+");
    }
}
