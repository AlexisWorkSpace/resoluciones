/* I - Rompiendo Rosarigasino: la transformación convierte una vocal v en "vGASv". Para deshacerla se busca
   cada posición i donde aparece v + "GAS" + v y se quitan los 4 caracteres "GASv". Se guardan solo las
   traducciones distintas, porque dos posiciones pueden dar la misma palabra (por ejemplo AGASAGASA). */
#include <stdio.h>
#include <string.h>

static int es_vocal(char c) { return c && strchr("AEIOU", c) != NULL; }

int main(void) {
    char w[128], trad[128][128];
    int cant = 0;
    if (scanf("%120s", w) != 1) return 0;
    int n = strlen(w);
    for (int i = 0; i + 4 < n; i++) {
        if (!es_vocal(w[i]) || strncmp(w + i + 1, "GAS", 3) != 0 || w[i + 4] != w[i]) continue;
        char t[128];
        memcpy(t, w, i + 1);
        strcpy(t + i + 1, w + i + 5);
        int repetida = 0;
        for (int j = 0; j < cant; j++) if (strcmp(trad[j], t) == 0) repetida = 1;
        if (!repetida) strcpy(trad[cant++], t);
    }
    if (cant == 0) printf("-\n");
    else if (cant == 1) printf("%s\n", trad[0]);
    else printf("+\n");
    return 0;
}
