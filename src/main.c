#include <stdio.h>
#include "artemis.h"
#include "calculadora.h"
#include "validaciones.h"

int main(void)
{
    Mision ultima = {0};     /* datos de la ultima mision jugada */
    int hay_reporte = 0;     /* 0 = todavia no se jugo ninguna */
    int opcion;

    do {
        printf("\n+==================================================+\n");
        printf("|        ARTEMIS - REINGRESO Y AMERIZAJE           |\n");
        printf("+==================================================+\n");
        printf(" 1. Iniciar mision\n");
        printf(" 2. Calculadora de analisis\n");
        printf(" 3. Reglas del juego\n");
        printf(" 4. Ver reporte de la ultima mision\n");
        printf(" 0. Salir\n");
        opcion = leer_entero("Elija una opcion", 0, 4);

        switch (opcion) {
        case 1:
            jugar_mision(&ultima);
            hay_reporte = 1;
            break;
        case 2:
            ejecutar_calculadora();
            break;
        case 3:
            mostrar_reglas();
            esperar_enter();
            break;
        case 4:
            if (hay_reporte) {
                mostrar_reporte(&ultima);
            } else {
                printf("\nTodavia no se jugo ninguna mision.\n");
            }
            esperar_enter();
            break;
        case 0:
            printf("\nHasta la proxima, comandante.\n");
            break;
        }
    } while (opcion != 0);

    return 0;
}
