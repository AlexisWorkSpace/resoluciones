# I - Rompiendo Rosarigasino: la transformación convierte una vocal v en "vGASv". Para deshacerla se busca
# cada posición i donde aparece v + "GAS" + v y se quitan los 4 caracteres "GASv". Las traducciones se
# guardan en un conjunto porque dos posiciones distintas pueden dar la misma palabra (por ejemplo AGASAGASA).
VOCALES = "AEIOU"

w = input().strip()
traducciones = set()
for i in range(len(w) - 4):
    if w[i] in VOCALES and w[i + 1:i + 4] == "GAS" and w[i + 4] == w[i]:
        traducciones.add(w[:i + 1] + w[i + 5:])

if not traducciones:
    print("-")
elif len(traducciones) == 1:
    print(traducciones.pop())
else:
    print("+")
