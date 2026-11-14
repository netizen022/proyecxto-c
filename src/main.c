#include <stdio.h>
#include <stdlib.h>
#include <string.h> // <--- AGREGÁ ESTA LÍNEA
#include "../include/artemis.h"
#include "../include/calculadora.h"
#include "../include/validaciones.h"

// ... el resto del código ...
#ifdef _WIN32
    #define POPEN _popen
    #define PCLOSE _pclose
#else
    #define POPEN popen
    #define PCLOSE pclose
#endif

// Función que verifica si la interfaz grafica ya esta abierta
int interfaz_ya_abierta() {
    FILE *f;
    char buffer[128];
    int encontrado = 0;

    // Ejecutamos "tasklist" de Windows y buscamos "interfaz_grafica.exe"
    f = POPEN("tasklist /FI \"IMAGENAME eq interfaz_grafica.exe\"", "r");
    if (f == NULL) return 0;

    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        if (strstr(buffer, "interfaz_grafica.exe") != NULL) {
            encontrado = 1;
            break;
        }
    }
    PCLOSE(f);
    return encontrado;
}

int main(void)
{
    NodoMision *historial = NULL; 
    int opcion;

    do {
        printf("\n+==================================================+\n");
        printf("|        ARTEMIS - REINGRESO Y AMERIZAJE           |\n");
        printf("+==================================================+\n");
        printf(" 1. Iniciar mision\n");
        printf(" 2. Calculadora de analisis\n");
        printf(" 3. Reglas del juego\n");
        printf(" 4. Ver historial de misiones\n");
        printf(" 0. Salir\n");
        opcion = leer_entero("Elija una opcion", 0, 4);

        switch (opcion) {
        case 1:
            // --- SOLO ABRIR SI NO ESTA ABIERTA ---
            if (!interfaz_ya_abierta()) {
                system("start interfaz_grafica.exe");
            }
            // -------------------------------------

            jugar_mision(&historial); 
            break;
        case 2:
            ejecutar_calculadora();
            break;
        case 3:
            mostrar_reglas();
            esperar_enter();
            break;
        case 4:
            mostrar_reporte(historial); 
            esperar_enter();
            break;
        case 0:
            printf("\nHasta la proxima, comandante.\n");
            break;
        }
    } while (opcion != 0);

    liberar_historial(&historial);

    return 0;
}