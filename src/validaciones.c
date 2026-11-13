#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

#define TAM_LINEA 128

/* Lee una linea completa. Devuelve 0 si hubo EOF/error, 1 si ok.
   Si la linea era mas larga que el buffer, descarta el resto para que
   no quede basura en stdin. */
static int leer_linea(char *buf, int tam)
{
    if (fgets(buf, tam, stdin) == NULL) {
        return 0;
    }
    if (strchr(buf, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            /* descartar */
        }
    }
    return 1;
}

int leer_entero(const char *mensaje, int min, int max)
{
    char linea[TAM_LINEA];
    int valor;
    char resto;

    while (1) {
        printf("%s [%d a %d]: ", mensaje, min, max);
        if (!leer_linea(linea, sizeof linea)) {
            printf("\nEntrada cerrada. Se usa el minimo (%d).\n", min);
            return min;
        }
        /* %d debe leer 1 campo y no puede haber texto extra luego del numero */
        if (sscanf(linea, "%d %c", &valor, &resto) != 1) {
            printf("  Error: ingrese un numero entero valido.\n");
            continue;
        }
        if (valor < min || valor > max) {
            printf("  Error: el valor debe estar entre %d y %d.\n", min, max);
            continue;
        }
        return valor;
    }
}

double leer_real(const char *mensaje, double min, double max)
{
    char linea[TAM_LINEA];
    double valor;
    char resto;

    while (1) {
        printf("%s [%g a %g]: ", mensaje, min, max);
        if (!leer_linea(linea, sizeof linea)) {
            printf("\nEntrada cerrada. Se usa el minimo (%g).\n", min);
            return min;
        }
        if (sscanf(linea, "%lf %c", &valor, &resto) != 1) {
            printf("  Error: ingrese un numero valido.\n");
            continue;
        }
        if (valor < min || valor > max) {
            printf("  Error: el valor debe estar entre %g y %g.\n", min, max);
            continue;
        }
        return valor;
    }
}

char leer_opcion(const char *mensaje, const char *opciones_validas)
{
    char linea[TAM_LINEA];
    char letra;
    char resto;

    while (1) {
        printf("%s [%s]: ", mensaje, opciones_validas);
        if (!leer_linea(linea, sizeof linea)) {
            printf("\nEntrada cerrada. Se usa '%c'.\n", opciones_validas[0]);
            return (char)tolower((unsigned char)opciones_validas[0]);
        }
        if (sscanf(linea, " %c %c", &letra, &resto) != 1) {
            printf("  Error: ingrese una sola letra de las opciones.\n");
            continue;
        }
        letra = (char)tolower((unsigned char)letra);
        if (strchr(opciones_validas, letra) == NULL) {
            printf("  Error: opcion no valida. Elija entre: %s\n", opciones_validas);
            continue;
        }
        return letra;
    }
}

void esperar_enter(void)
{
    char linea[TAM_LINEA];
    printf("\nPresione Enter para continuar...");
    leer_linea(linea, sizeof linea);
}
