#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/* Lectura segura de datos por consola.
   Todas leen la linea completa con fgets, convierten con sscanf verificando
   su retorno, avisan el error y repiten hasta que el dato sea valido. */

/* Pide un entero en el rango [min, max]. */
int leer_entero(const char *mensaje, int min, int max);

/* Pide un numero real en el rango [min, max]. */
double leer_real(const char *mensaje, double min, double max);

/* Pide un caracter que este dentro de opciones_validas (ej: "sn").
   No distingue mayusculas de minusculas; devuelve la letra en minuscula. */
char leer_opcion(const char *mensaje, const char *opciones_validas);

/* Pausa hasta que el usuario presione Enter. */
void esperar_enter(void);

#endif /* VALIDACIONES_H */
