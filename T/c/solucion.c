/* T - Test: leer dos enteros e imprimir su suma. */
#include <stdio.h>

int main(void) {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2) return 0;
    printf("%d\n", a + b);
    return 0;
}
