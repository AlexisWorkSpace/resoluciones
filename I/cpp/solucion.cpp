// I - Rompiendo Rosarigasino: la transformación convierte una vocal v en "vGASv". Para deshacerla se busca
// cada posición i donde aparece v + "GAS" + v y se quitan los 4 caracteres "GASv". Las traducciones se
// guardan en un set porque dos posiciones distintas pueden dar la misma palabra (por ejemplo AGASAGASA).
#include <bits/stdc++.h>
using namespace std;

int main() {
    string w;
    cin >> w;
    const string vocales = "AEIOU";
    set<string> traducciones;
    for (int i = 0; i + 4 < (int)w.size(); i++)
        if (vocales.find(w[i]) != string::npos && w.compare(i + 1, 3, "GAS") == 0 && w[i + 4] == w[i])
            traducciones.insert(w.substr(0, i + 1) + w.substr(i + 5));
    if (traducciones.empty()) cout << "-\n";
    else if (traducciones.size() == 1) cout << *traducciones.begin() << '\n';
    else cout << "+\n";
}
