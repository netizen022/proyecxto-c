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
