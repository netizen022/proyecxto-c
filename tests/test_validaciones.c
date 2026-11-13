/* Prueba manual de validaciones. Probar con: letras, linea vacia,
   fuera de rango, "12abc", "3.5" en entero, y valores validos.
   Compilar: make test_validaciones */
#include <stdio.h>
#include "../include/validaciones.h"

int main(void)
{
    int n = leer_entero("Entero", 0, 10);
    printf("-> leyo entero: %d\n", n);

    double x = leer_real("Real", 0.0, 90.0);
    printf("-> leyo real: %.3f\n", x);

    char c = leer_opcion("Continuar (s/n)", "sn");
    printf("-> leyo opcion: %c\n", c);

    esperar_enter();
    printf("Fin de pruebas.\n");
    return 0;
}
