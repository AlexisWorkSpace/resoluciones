/* D - Algoritmo Extraño: simulación directa. Se usa long long porque los valores intermedios superan 2^31. */
#include <stdio.h>

int main(void) {
    long long n;
    if (scanf("%lld", &n) != 1) return 0;
    printf("%lld", n);
    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        printf(" %lld", n);
    }
    printf("\n");
    return 0;
}
