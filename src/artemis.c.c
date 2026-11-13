#include <stdio.h>
#include <stdlib.h>
#include "../include/artemis.h"
#include "../include/fisica.h"
#include "../include/validaciones.h"

/* Función auxiliar privada recursiva (no se declara en el .h).
   Recorre la lista e imprime cada misión usando recursividad de cola. */
static void reporte_recursivo(NodoMision *nodo, int num_mision)
{
    /* Caso base: si el puntero es NULL, llegamos al final de la lista */
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

void jugar_mision(NodoMision **historial)
{
    double angulo;
    int evaluacion;

    /* 1. Uso de memoria dinámica (malloc) para el nuevo nodo de la lista */
    NodoMision *nuevo_nodo = (NodoMision *)malloc(sizeof(NodoMision));
    if (nuevo_nodo == NULL) {
        printf("Error: No hay memoria suficiente para iniciar la mision.\n");
        return;
    }

    printf("\n--- SECUENCIA DE REINGRESO INICIADA ---\n");
    angulo = leer_real("Comandante, ingrese el angulo de reingreso [grados]", 0.0, 90.0);
    
    nuevo_nodo->info.angulo_ingreso = angulo;
    evaluacion = evaluar_angulo(angulo);

    if (evaluacion == 1) {
        printf("\n[EXITO] Angulo nominal. La capsula penetra la atmosfera de forma segura.\n");
        printf("Paracaidas desplegados. Amerizaje confirmado.\n");
        nuevo_nodo->info.estado_partida = 1;
    } else if (evaluacion == 0) {
        printf("\n[FRACASO] Angulo muy rasante. La capsula reboto en la alta atmosfera.\n");
        printf("Se perdio el contacto. La mision ha fallado.\n");
        nuevo_nodo->info.estado_partida = 2;
    } else {
        printf("\n[FRACASO] Angulo muy empinado. Desaceleracion brutal y escudos superados.\n");
        printf("La capsula se desintegro por el calor.\n");
        nuevo_nodo->info.estado_partida = 2;
    }

    /* 2. Cálculos físicos apoyándose en la librería del compañero */
    nuevo_nodo->info.trabajo_roz = trabajo_rozamiento(MASA_ORION, VELOCIDAD_INICIAL, 25.0, 
                                                      ALTURA_INICIAL, 2500.0, GRAVEDAD);
    nuevo_nodo->info.desaceleracion = desaceleracion_media(VELOCIDAD_INICIAL, 25.0, 400.0);
    nuevo_nodo->info.fuerza_impacto = fuerza_amerizaje(MASA_ORION, 8.0, 1.5, GRAVEDAD);

    /* 3. Inserción al principio de la lista enlazada (actualizamos la cabeza) */
    nuevo_nodo->sig = *historial;
    *historial = nuevo_nodo;
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

    /* Recorremos iterativamente solo para saber cuántas misiones hay y numerarlas */
    while (aux != NULL) {
        cantidad++;
        aux = aux->sig;
    }

    /* Disparamos la función recursiva pasándole la cabeza de la lista */
    reporte_recursivo(historial, cantidad);
    
    printf("+==================================================+\n");
}

void liberar_historial(NodoMision **historial)
{
    NodoMision *aux;
    /* Liberamos la memoria dinámica (free) para no dejar memory leaks */
    while (*historial != NULL) {
        aux = *historial;
        *historial = (*historial)->sig;
        free(aux);
    }
}