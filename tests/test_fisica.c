#include <stdio.h>
#include "../include/fisica.h"

int main() {
    // Datos nominales de la consigna
    double m = 10400.0;
    double vi = 11000.0;
    double vf = 25.0;
    double hi = 120000.0;
    double hf = 2500.0;
    double g = 9.81;
    double dt = 400.0;
    double d = 1.5;
    double v_imp = 8.0;

    printf("--- EJECUTANDO PRUEBAS DE FISICA ---\n");

    // Probar Trabajo de Rozamiento (Punto A)
    double w_roz = trabajo_rozamiento(m, vi, vf, hi, hf, g);
    printf("W_roz = %.2e J (Esperado aprox: -6.41e+11 J)\n", w_roz);

    // Probar Desaceleración Media (Punto B)
    double a_med = desaceleracion_media(vi, vf, dt);
    double ng = a_multiplos_g(a_med, g);
    printf("A_med = %.2f m/s^2 | En g: %.2f g (Esperado aprox: 2.80 g)\n", a_med, ng);

    // Probar Fuerza de Amerizaje (Punto C)
    double f_prom = fuerza_amerizaje(m, v_imp, d, g);
    double peso = m * g;
    printf("F_prom = %.2f N | Multiplo del peso: %.2f\n", f_prom, f_prom / peso);

    // Probar Ángulos (Punto D)
    printf("Angulo 6.0 deg (Seguro): %d (Esperado 1)\n", evaluar_angulo(6.0));
    printf("Angulo 4.0 deg (Rasante): %d (Esperado 0)\n", evaluar_angulo(4.0));
    printf("Angulo 8.0 deg (Empinado): %d (Esperado -1)\n", evaluar_angulo(8.0));

    return 0;
}