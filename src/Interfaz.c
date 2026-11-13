#include <stdio.h>
#include "../include/interfaz.h"
#include "../include/fisica.h"

/* Funcion auxiliar privada recursiva (no se declara en el .h).
   Recorre la lista e imprime cada mision usando recursividad de cola. */
static void reporte_recursivo(NodoMision *nodo, int num_mision)
{
    /* Caso base: llegamos al final de la lista */
    if (nodo == NULL) {
        return; 
    }

    printf("\n--- MISION %d ---\n", num_mision);
    printf(" Resultado:             %s\n", (nodo->info.estado_partida == 1) ? "EXITO" : "DESTRUIDA");
    printf(" Angulo de ingreso:     %.2f grados\n", nodo->info.angulo_ingreso);
    printf(" Trabajo de rozamiento: %.3e J\n", nodo->info.trabajo_roz);
    printf(" Desaceleracion media:  %.2f m/s^2 (%.2f Gs)\n", 
            nodo->info.desaceleracion, a_multiplos_g(nodo->info.desaceleracion, GRAVEDAD));
    printf(" Fuerza en amerizaje:   %.2f N\n", nodo->info.fuerza_impacto);

    /* Llamada recursiva avanzando al siguiente nodo */
    reporte_recursivo(nodo->sig, num_mision - 1);
}

void mostrar_reglas(void)
{
    printf("\n+==================================================+\n");
    printf("|              REGLAS DE LA MISION                 |\n");
    printf("+==================================================+\n");
    printf(" 1. Tu objetivo es guiar la capsula Orion a la Tierra.\n");
    printf(" 2. Debes ingresar a la atmosfera con el angulo correcto.\n");
    printf(" 3. Si es menor a %.1f grados, rebotaras al espacio.\n", ANGULO_MINIMO);
    printf(" 4. Si es mayor a %.1f grados, te quemaras por friccion.\n", ANGULO_MAXIMO);
    printf(" 5. Si acertas el angulo, la tripulacion amerizara a salvo.\n");
    printf("+==================================================+\n");
}

void mostrar_reporte(NodoMision *historial)
{
    int cantidad = 0;
    NodoMision *aux = historial;
    
    printf("\n+==================================================+\n");
    printf("|        HISTORIAL DE MISIONES (RECURSIVO)         |\n");
    printf("+==================================================+\n");
    
    if (historial == NULL) {
        printf(" Error: No hay registros. Inicia una mision primero.\n");
        printf("+==================================================+\n");
        return;
    }

    /* Recorremos iterativamente solo para saber cuantas misiones hay y numerarlas */
    while (aux != NULL) {
        cantidad++;
        aux = aux->sig;
    }

    /* Disparamos la funcion recursiva pasandole la cabeza de la lista */
    reporte_recursivo(historial, cantidad);
    
    printf("+==================================================+\n");
}
