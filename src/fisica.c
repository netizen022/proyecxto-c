#include "fisica.h"
#include <math.h>

// 1. Energía cinética: Ec = 0.5 * m * v^2
double energia_cinetica(double masa, double velocidad) {
    return 0.5 * masa * pow(velocidad, 2);
}

// 2. Trabajo de la fuerza de rozamiento (Teorema del Trabajo y la Energía)
// W_roz = delta(Ec) + delta(Ep)
double trabajo_rozamiento(double masa, double v_inicial, double v_final, double h_inicial, double h_final, double g) {
    double delta_ec = energia_cinetica(masa, v_final) - energia_cinetica(masa, v_inicial);
    double delta_ep = masa * g * (h_final - h_inicial);
    return delta_ec + delta_ep;
}

// 3. Desaceleración media: a_med = |v_f - v_i| / dt
double desaceleracion_media(double v_inicial, double v_final, double delta_t) {
    if (delta_t <= 0) return 0.0;
    return fabs(v_final - v_inicial) / delta_t;
}

// 4. Conversión de aceleración a múltiplos de g
double a_multiplos_g(double aceleracion, double g) {
    if (g <= 0) return 0.0;
    return aceleracion / g;
}

// 5. Fuerza promedio en el amerizaje: F_prom = ((1/2 * m * v_impacto^2) / d) + m*g
double fuerza_amerizaje(double masa, double v_impacto, double profundidad, double g) {
    if (profundidad <= 0) return 0.0;
    double trabajo_cinetico = energia_cinetica(masa, v_impacto);
    double peso = masa * g;
    return (trabajo_cinetico / profundidad) + peso;
}

// 6. Evaluación del ángulo de reingreso (gamma en grados)
// Ventana segura: 5.5° <= gamma <= 7.0°
int evaluar_angulo(double gamma) {
    if (gamma < 5.5) {
        return 0;  // Rebote atmosférico (muy rasante)
    } else if (gamma > 7.0) {
        return -1; // Desaceleración excesiva / sobrecalentamiento (muy empinado)
    } else {
        return 1;  // Dentro de la ventana segura
    }
}