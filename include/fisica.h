#ifndef FISICA_H
#define FISICA_H

// Declaración de funciones puras para el cálculo físico del Reingreso Orion
double energia_cinetica(double masa, double velocidad);

double trabajo_rozamiento(double masa, double v_inicial, double v_final, double h_inicial, double h_final, double g);

double desaceleracion_media(double v_inicial, double v_final, double delta_t);

double a_multiplos_g(double aceleracion, double g);

double fuerza_amerizaje(double masa, double v_impacto, double profundidad, double g);

// Devuelve: 1 si es seguro, 0 si es rasante (< 5.5), -1 si es empinado (> 7.0)
int evaluar_angulo(double gamma);

#endif