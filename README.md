# Lab_C_GRUPO-14 - Simulador Artemis: Reingreso y Amerizaje

Trabajo Practico Integrador Final - Algoritmos y Estructuras de Datos
UTN Facultad Regional Resistencia - Ingenieria en Sistemas de Informacion

## Integrantes

Comisión: K1.1

| Integrante | Módulo a cargo |
|---|---|
| Pelozo, Ángel Esteban | Preparación del repositorio, Makefile y validaciones |
| Frettis, Andrés | Cabeceras, interfaz, reglas y reporte |
| Méndez, Thiago | Funciones físicas y pruebas |
| Noguera Vega, Juan Sebastián | Lógica de las etapas de la misión |
| Alegre Prieto, Elías | Menú principal, calculadora y README |

## Escenario asignado

**Situacion-Problema 4: Reingreso atmosferico, frenado aerodinamico y amerizaje**
(Trabajo, Energia e Impacto). Modulo de tripulacion Orion de 10.400 kg que reingresa
a 11.000 m/s desde 120.000 m, abre paracaidas a 2.500 m con 25 m/s y amerriza a 8 m/s.

## Funcionamiento

El programa se ejecuta por consola y ofrece un menu principal:

1. **Iniciar mision:** simulacion por turnos en 3 fases (reingreso, frenado, amerizaje).
2. **Calculadora de analisis:** responde los puntos a, b, c y d de la consigna con los
   datos de la consigna o con datos ingresados por el usuario.
3. **Reglas del juego.**
4. **Ver historial de todas las misiones de la sesión.**
0. **Salir.**

### Calculos fisicos

- Energia cinetica: `Ec = 1/2 * m * v^2`
- Trabajo de rozamiento (trabajo-energia): `W_roz = (Ec_f - Ec_i) + m*g*(h_f - h_i)`
- Desaceleracion media: `a = |v_f - v_i| / dt`, y en multiplos de g: `a / g`
- Fuerza promedio de amerizaje: `F_prom = Ec / d + m*g`
- Ventana de reingreso: `5,5 <= gamma <= 7,0` grados. Si `gamma > 7,0` la desaceleracion es
  excesiva; si `gamma < 5,5` hay rebote atmosferico.

Valor de gravedad utilizado: **g = 9,81 m/s2** (la consigna no lo define para este escenario).

### Resultados con los datos de la consigna

| Calculo | Resultado |
|---|---|
| W_roz | -6,412 x 10^11 J |
| Desaceleracion media | 27,44 m/s2 (2,80 g) |
| F_prom | 323.891 N (3,17 veces el peso) |

## Estructura del proyecto

```
include/   cabeceras (.h): artemis.h, fisica.h, interfaz.h, validaciones.h, calculadora.h
src/       codigo fuente (.c): main.c, artemis.c, fisica.c, interfaz.c, validaciones.c, calculadora.c
tests/     pruebas: test_fisica.c
Makefile   compilacion
```

## Compilacion y ejecucion

Con `make` (requiere gcc):

```
make
./artemis
```

Sin `make`, a mano:

```
gcc -Wall -Iinclude src/*.c -o artemis -lm
./artemis
```

En Windows (MinGW) el ejecutable se llama `artemis.exe`. El enlace con `-lm` es necesario
porque `fisica.c` usa `math.h` (`pow`, `fabs`).

## Validaciones

Toda entrada del usuario se lee con `fgets` y se convierte con `sscanf`, verificando su
retorno. Si el dato no es un numero o esta fuera de rango, se informa el error y se vuelve a
pedir, por lo que el programa no se cierra ni entra en un bucle infinito.

## Registro de uso de Inteligencia Artificial

| Herramienta | Para que se uso | Consultas principales | Como se valido |
|---|---|---|---|
| Claude (Anthropic) | Planificacion del proyecto, reparto de tareas, borrador de `main.c` y `calculadora.c`, explicacion de Git/GitHub | Arquitectura modular segun el material de la catedra; menu con do-while y switch; calculadora de los puntos a-d; como subir commits a una rama y abrir un Pull Request | Se compilo con `gcc -Wall -Wextra`, se probo con entradas validas e invalidas y se comparo con calculos hechos a mano |
| ChatGPT (OpenAI), utilizado por Juan Sebastián Noguera Vega | Revisión e integración de la lógica de misión, corrección de cabeceras y funciones duplicadas, creación de validaciones y ayuda con GitHub | Cómo conectar ejecutarMision con jugar_mision; corregir errores de compilación; validar entradas; actualizar ramas e integrar cambios | Se compiló el ZIP con gcc -Wall y se ejecutaron pruebas de física y misiones con ángulos de 4°, 6° y 8°, comprobando los resultados y el historial |

> Completar: cada integrante agrega aqui sus propias consultas a IA y como valido el resultado.
