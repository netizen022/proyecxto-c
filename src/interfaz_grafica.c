#include "raylib.h"
#include "fisica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define G 9.81

int main(void) {
    const int screenWidth = 1000;
    const int screenHeight = 700;
    InitWindow(screenWidth, screenHeight, "Artemis - Pantalla de Telemetria");
    SetTargetFPS(60);

    double masa = 0, v_ini = 0, v_fin = 0, gamma = 0, prof = 0;
    double res_energia = 0, res_trabajo = 0, res_desacel = 0, res_mult_g = 0, res_fuerza = 0;
    int res_angulo = 0;
    bool calculado = false;
    
    bool animando = false;
    float nave_y = 120.0f; 
    float nave_velocidad = 2.0f;
    float tiempo_animacion = 0.0f;
    Color color_nave = WHITE;

    float timer_lectura = 0.0f;

    while (!WindowShouldClose()) {
        // Leer archivo de datos
        timer_lectura += GetFrameTime();
        if (timer_lectura > 0.5f) { 
            timer_lectura = 0.0f;
            FILE *archivo = fopen("datos_mision.txt", "r");
            if (archivo != NULL) {
                double m, vi, vf, g, p;
                // Leemos los 5 valores
                if (fscanf(archivo, "%lf %lf %lf %lf %lf", &m, &vi, &vf, &g, &p) == 5) {
                    // Si los datos cambiaron, recalculamos y animamos
                    if (m != masa || vi != v_ini || vf != v_fin || g != gamma) {
                        masa = m; v_ini = vi; v_fin = vf; gamma = g; prof = p;
                        
                        res_energia = energia_cinetica(masa, v_ini);
                        res_trabajo = trabajo_rozamiento(masa, v_ini, v_fin, 120000, 0, G);
                        res_desacel = desaceleracion_media(v_ini, v_fin, 5.0);
                        res_mult_g = a_multiplos_g(res_desacel, G);
                        res_fuerza = fuerza_amerizaje(masa, v_fin, prof, G);
                        res_angulo = evaluar_angulo(gamma);
                        
                        calculado = true;
                        animando = true;
                        nave_y = 120.0f; 
                        tiempo_animacion = 0.0f;
                        nave_velocidad = (v_fin / 100.0f) + 1.0f; 
                    }
                }
                fclose(archivo);
                remove("datos_mision.txt"); // Borrar para no repetir
            }
        }

        // Lógica de animación
        if (animando) {
            tiempo_animacion += GetFrameTime();
            nave_y += nave_velocidad;
            
            if (res_angulo == 1) color_nave = GREEN;
            else if (res_angulo == 0) color_nave = ORANGE;
            else color_nave = (fmod(tiempo_animacion, 0.2f) < 0.1f) ? RED : (Color){255, 100, 100, 255};

            if (nave_y >= 500.0f) { 
                nave_y = 500.0f;
                animando = false;
            }
        }

        // --- DIBUJADO ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("PANEL DE TELEMETRIA ARTEMIS", 50, 20, 30, DARKBLUE);
        DrawLine(50, 60, 950, 60, LIGHTGRAY);

        // --- PANEL IZQUIERDO: RESULTADOS ---
        DrawRectangle(50, 80, 400, 580, (Color){240, 240, 240, 255});
        DrawRectangleLines(50, 80, 400, 580, GRAY);
        DrawText("DATOS DE LA SIMULACION", 70, 100, 20, DARKBLUE);
        
        if (calculado) {
            int y = 140;
            DrawText(TextFormat("Masa: %.1f kg", masa), 70, y, 20, BLACK); y += 30;
            DrawText(TextFormat("Vel. Inicial: %.1f m/s", v_ini), 70, y, 20, BLACK); y += 30;
            DrawText(TextFormat("Vel. Final: %.1f m/s", v_fin), 70, y, 20, BLACK); y += 30;
            DrawText(TextFormat("Angulo Gamma: %.1f grados", gamma), 70, y, 20, BLACK); y += 40;

            DrawLine(70, y, 430, y, GRAY); y += 20;

            DrawText(TextFormat("Energia Cinetica: %.0f J", res_energia), 70, y, 18, BLACK); y += 30;
            DrawText(TextFormat("Trabajo Rozamiento: %.0f J", res_trabajo), 70, y, 18, BLACK); y += 30;
            DrawText(TextFormat("Desaceleracion: %.1f m/s2", res_desacel), 70, y, 18, BLACK); y += 30;
            DrawText(TextFormat("Aceleracion: %.1f g", res_mult_g), 70, y, 18, BLACK); y += 30;
            DrawText(TextFormat("Fuerza Amerizaje: %.0f N", res_fuerza), 70, y, 18, BLACK); y += 40;
            
            if (res_angulo == 1) {
                DrawText("ESTADO: ANGULO SEGURO", 70, y, 22, GREEN);
            } else if (res_angulo == 0) {
                DrawText("ESTADO: MUY RASANTE", 70, y, 22, ORANGE);
            } else {
                DrawText("ESTADO: MUY EMPINADO", 70, y, 22, RED);
            }
        } else {
            DrawText("Esperando inicio de mision...", 70, 150, 18, DARKGRAY);
        }

        // --- PANEL DERECHO: ANIMACIÓN ---
        DrawRectangle(480, 80, 470, 580, (Color){230, 240, 255, 255}); 
        DrawRectangleLines(480, 80, 470, 580, GRAY);
        DrawText("Animacion de Reingreso", 500, 100, 20, DARKBLUE);

        // La Tierra
        DrawCircle(715, 650, 150, (Color){100, 150, 200, 255}); 
        
        // La Nave
        if (calculado) {
            Vector2 v1 = {715, nave_y - 15};
            Vector2 v2 = {700, nave_y + 15};
            Vector2 v3 = {730, nave_y + 15};
            DrawTriangle(v1, v3, v2, color_nave); 
            DrawTriangleLines(v1, v3, v2, BLACK);

            if (res_angulo == -1 && animando) {
                DrawTriangle((Vector2){715, nave_y - 25}, (Vector2){705, nave_y - 15}, (Vector2){725, nave_y - 15}, ORANGE);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}