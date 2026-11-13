#include <stdio.h>
#include "calculadora.h"
#include "fisica.h"
#include "validaciones.h"

#define G_TIERRA 9.81   /* unificar con artemis.h cuando este cerrado */

/* Datos del problema agrupados en un solo tipo */
typedef struct {
    double masa;         /* kg  */
    double v_inicial;    /* m/s */
    double v_final;      /* m/s (apertura de paracaidas) */
    double h_inicial;    /* m   */
    double h_final;      /* m   */
    double delta_t;      /* s   */
    double profundidad;  /* m   */
    double v_impacto;    /* m/s */
} DatosReingreso;

static void linea(void)
{
    printf("+--------------------------------------------------+\n");
}

static void cargar_datos_consigna(DatosReingreso *d)
{
    d->masa        = 10400.0;
    d->v_inicial   = 11000.0;
    d->v_final     = 25.0;
    d->h_inicial   = 120000.0;
    d->h_final     = 2500.0;
    d->delta_t     = 400.0;
    d->profundidad = 1.5;
    d->v_impacto   = 8.0;
}

static void pedir_datos_usuario(DatosReingreso *d)
{
    d->masa      = leer_real("Masa de la capsula [kg]", 1.0, 1000000.0);
    d->v_inicial = leer_real("Rapidez inicial de reingreso [m/s]", 1.0, 20000.0);
    d->v_final   = leer_real("Rapidez al abrir paracaidas [m/s]", 0.0, d->v_inicial);
    d->h_inicial = leer_real("Altitud inicial [m]", 1.0, 200000.0);
    d->h_final   = leer_real("Altitud de apertura de paracaidas [m]", 0.0, d->h_inicial);
    d->delta_t   = leer_real("Duracion de la fase de mayor desaceleracion [s]", 0.1, 10000.0);
    d->profundidad = leer_real("Profundidad de hundimiento en el agua [m]", 0.01, 100.0);
    d->v_impacto = leer_real("Rapidez de impacto en el agua [m/s]", 0.0, 1000.0);
}

static void punto_a(const DatosReingreso *d)
{
    double ec_i = energia_cinetica(d->masa, d->v_inicial);
    double ec_f = energia_cinetica(d->masa, d->v_final);
    double w = trabajo_rozamiento(d->masa, d->v_inicial, d->v_final,
                                  d->h_inicial, d->h_final, G_TIERRA);
    linea();
    printf("| PUNTO A - Trabajo de la fuerza de rozamiento     |\n");
    linea();
    printf("Ec inicial = %.3e J\n", ec_i);
    printf("Ec final   = %.3e J\n", ec_f);
    printf("W_roz = (Ec_f - Ec_i) + m*g*(h_f - h_i) = %.3e J\n", w);
    printf("(negativo: el aire le quita energia a la capsula)\n");
}

static void punto_b(const DatosReingreso *d)
{
    double a  = desaceleracion_media(d->v_inicial, d->v_final, d->delta_t);
    double ng = a_multiplos_g(a, G_TIERRA);
    linea();
    printf("| PUNTO B - Desaceleracion media de la tripulacion |\n");
    linea();
    printf("a_media = |v_f - v_i| / dt = %.2f m/s^2\n", a);
    printf("En multiplos de g         = %.2f g\n", ng);
}

static void punto_c(const DatosReingreso *d)
{
    double f    = fuerza_amerizaje(d->masa, d->v_impacto, d->profundidad, G_TIERRA);
    double peso = d->masa * G_TIERRA;
    linea();
    printf("| PUNTO C - Fuerza promedio en el amerizaje        |\n");
    linea();
    printf("F_prom = Ec/d + m*g = %.2f N\n", f);
    printf("Peso de la nave     = %.2f N\n", peso);
    printf("F_prom / peso       = %.2f veces el peso\n", f / peso);
}

static void punto_d(void)
{
    double gamma;
    int estado;

    linea();
    printf("| PUNTO D - Angulo de reingreso (ventana 5.5-7.0)  |\n");
    linea();
    gamma = leer_real("Angulo de reingreso gamma [grados]", 0.0, 90.0);
    estado = evaluar_angulo(gamma);

    switch (estado) {
    case 1:
        printf("gamma = %.2f grados: DENTRO de la ventana segura.\n", gamma);
        printf("La desaceleracion y el calentamiento son tolerables.\n");
        break;
    case -1:
        printf("gamma = %.2f grados: demasiado EMPINADO (> 7.0).\n", gamma);
        printf("La capsula entra a capas densas muy rapido: desaceleracion\n");
        printf("excesiva (mas g sobre la tripulacion) y sobrecalentamiento\n");
        printf("del escudo termico.\n");
        break;
    default:
        printf("gamma = %.2f grados: demasiado RASANTE (< 5.5).\n", gamma);
        printf("La capsula no penetra lo suficiente: rebota en la atmosfera\n");
        printf("y vuelve al espacio sin completar el reingreso.\n");
        break;
    }
}

void ejecutar_calculadora(void)
{
    DatosReingreso datos;
    int datos_cargados = 0;
    int opcion;

    do {
        printf("\n+==================================================+\n");
        printf("|      CALCULADORA DE ANALISIS - REINGRESO         |\n");
        printf("+==================================================+\n");
        printf(" 1. Usar datos de la consigna\n");
        printf(" 2. Ingresar mis propios datos\n");
        printf(" 3. Punto A - Trabajo de rozamiento\n");
        printf(" 4. Punto B - Desaceleracion media\n");
        printf(" 5. Punto C - Fuerza de amerizaje\n");
        printf(" 6. Punto D - Analisis del angulo\n");
        printf(" 7. Calcular A, B y C juntos\n");
        printf(" 0. Volver al menu principal\n");
        opcion = leer_entero("Elija una opcion", 0, 7);

        if (opcion >= 3 && opcion <= 7 && opcion != 6 && !datos_cargados) {
            printf("\n[!] Primero cargue datos (opcion 1 o 2).\n");
            continue;
        }

        switch (opcion) {
        case 1:
            cargar_datos_consigna(&datos);
            datos_cargados = 1;
            printf("\nDatos de la consigna cargados.\n");
            break;
        case 2:
            pedir_datos_usuario(&datos);
            datos_cargados = 1;
            printf("\nDatos propios cargados.\n");
            break;
        case 3: punto_a(&datos); break;
        case 4: punto_b(&datos); break;
        case 5: punto_c(&datos); break;
        case 6: punto_d(); break;
        case 7:
            punto_a(&datos);
            punto_b(&datos);
            punto_c(&datos);
            break;
        default:
            break;
        }
        if (opcion != 0) {
            esperar_enter();
        }
    } while (opcion != 0);
}
