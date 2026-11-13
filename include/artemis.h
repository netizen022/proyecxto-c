#ifndef ARTEMIS_H
#define ARTEMIS_H

// Constantes del Escenario 4 - Reingreso Orion 
#define GRAVEDAD 9.81
#define MASA_ORION 10400.0
#define VELOCIDAD_INICIAL 11000.0
#define ALTURA_INICIAL 120000.0
#define ANGULO_MINIMO 5.5
#define ANGULO_MAXIMO 7.0

// Estructura con los datos de una mision individual //
typedef struct {
    int estado_partida;       /* 0: no jugada, 1: victoria, 2: destruida */
    double angulo_ingreso;
    double trabajo_roz;
    double desaceleracion;
    double fuerza_impacto;
} Mision;

// Nodo para armar la lista simplemente enlazada del historial //
typedef struct NodoMision {
    Mision info;
    struct NodoMision *sig;
} NodoMision;

// Prototipos principales //
void mostrar_reglas(void);

//* Recibe un puntero doble porque va a modificar la cabeza de la lista 
   
//agregando una nueva mision al historial con malloc //

void jugar_mision(NodoMision **historial);

// Funcion wrapper (envoltorio) para ocultar la recursividad al main 
void mostrar_reporte(NodoMision *historial);

// Libera la memoria al cerrar el juego para no dejar memory leaks 

void liberar_historial(NodoMision **historial);

#endif /* ARTEMIS_H */
