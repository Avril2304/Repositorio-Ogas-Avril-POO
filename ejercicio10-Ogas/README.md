# Ejercicio 10 - T-Rex Extremo

Aplicación desarrollada en C++ con Qt Widgets, inspirada en el clásico juego del T-Rex de Google Chrome.  
El jugador controla un dinosaurio que debe esquivar cactus y pájaros, utilizando eventos de teclado, temporizadores y detección de colisiones.

## Objetivo

Implementar un juego de escritorio en Qt aplicando:

- Herencia
- Modularización de clases
- Eventos de teclado
- Temporizadores con `QTimer`
- Detección de colisiones
- Renderizado con `QPainter`
- Recursos gráficos mediante `.qrc`

## Controles

|       Tecla      |             Acción             |
|------------------|--------------------------------|
| Espacio          | Saltar                         |
| Flecha abajo     | Agacharse                      |
| Flecha derecha   | Adelantarse                    |
| Flecha izquierda | Frenarse                       |
| R                | Reiniciar luego del Game Over  |

## Clases principales

|    Clase    |                        Responsabilidad                        |
|-------------|---------------------------------------------------------------|
| `Juego`     | Ventana principal, renderizado, timers generales y colisiones |
| `TRex`      | Controla posición, salto, agacharse y movimiento horizontal   |
| `Obstaculo` | Clase base abstracta para obstáculos                          |
| `Cactus`    | Obstáculo terrestre controlado por el timer principal         |
| `Pajaro`    | Obstáculo aéreo con `QTimer` independiente por instancia      |

## Funcionamiento general

La clase `Juego` hereda de `QWidget` y utiliza `paintEvent()` para dibujar el escenario, el dinosaurio, los cactus, los pájaros, el puntaje y el estado de Game Over.

El juego utiliza un `QTimer` principal que actualiza el movimiento del cactus, el salto del T-Rex, el puntaje, la dificultad y la detección de colisiones.

Cada pájaro posee su propio `QTimer`, lo que permite que cada instancia se mueva de forma independiente. Además, cada 5 segundos aparece un nuevo pájaro con altura aleatoria.

## Dificultad progresiva

A medida que aumenta el puntaje, también aumenta el nivel de velocidad.  
Esto afecta el movimiento de los cactus y de los pájaros, haciendo que el juego sea cada vez más difícil.

## Recursos gráficos

Las imágenes se cargan mediante un archivo de recursos de Qt:

```pro
RESOURCES += recursos.qrc
````

Esto permite incluir las imágenes directamente en el ejecutable, evitando depender de rutas externas dentro de la carpeta `build`.

## Compilación y ejecución

1. Abrir el proyecto en Qt Creator.
2. Ejecutar `Run qmake`.
3. Compilar con `Build`.
4. Ejecutar el proyecto.

## Tecnologías utilizadas

* C++
* Qt Widgets
* QTimer
* QPainter
* QKeyEvent
* Qt Resource System `.qrc`