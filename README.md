# Programación Orientada a Objetos - Trabajos Prácticos

Repositorio correspondiente a la materia **Programación Orientada a Objetos**, donde se desarrollan distintos ejercicios prácticos utilizando **C++ y Qt Framework**.

El objetivo principal del repositorio es centralizar y documentar todos los trabajos realizados durante la cursada, manteniendo una estructura organizada, modular y escalable para cada ejercicio.

---

# Estructura del repositorio

```text
Repositorio-Ogas-Avril-POO/
│
├── ejercicio01-Ogas/
├── ejercicio02-Ogas/
├── ejercicio03-Ogas-Poletto-Agostini/
├── ejercicio04-Ogas-Poletto-Agostini/
├── ejercicio05-Ogas/
├── ejercicio06-Ogas/
├── ejercicio07-Ogas/
├── ejercicio08-Ogas/
├── ejercicio09-Ogas/
├── ejercicio10-Ogas/
│
├── .gitignore
└── README.md
```

---

# Ejercicios

## Ejercicio 01 - Planificador de trabajos prácticos

Aplicación de escritorio desarrollada en Qt para organizar trabajos prácticos.
Incluye login con usuarios locales, persistencia de sesión, tablero de tareas en grilla, filtros por estado y prioridad, edición de trabajos, editor de notas e historial de acciones.

---

## Ejercicio 02 - Panel de monitoreo VPS

Aplicación Qt que funciona como panel de monitoreo de un servidor VPS.
Consume un endpoint HTTP que devuelve información de estado del servidor, incluyendo uptime, carga, memoria y almacenamiento. La interfaz muestra métricas principales, historial de eventos y controles de actualización.

---

## Ejercicio 03 - Lienzo colaborativo en tiempo real

Aplicación colaborativa de dibujo desarrollada con Qt.
Permite dibujar a mano alzada utilizando `paintEvent`, con suavizado de trazos, interpolación de puntos, selección dinámica de colores y sincronización mediante un backend conectado al VPS.

---

## Ejercicio 04 - Tablero Kanban colaborativo

Aplicación de escritorio basada en Qt para administrar tareas tipo Kanban utilizando una API desarrollada con FastAPI y persistencia en MySQL.
Permite crear, editar y mover tarjetas entre columnas, manteniendo sincronización colaborativa entre usuarios.

---

## Ejercicio 05 - Login sin QtDesigner

Aplicación de login desarrollada completamente desde código en un proyecto vacío de Qt.
La interfaz se construye manualmente utilizando widgets, layouts, señales y slots.

---

## Ejercicio 06 - Login con QtDesigner

Aplicación de login desarrollada utilizando QtDesigner.
Trabaja con formularios `.ui`, validación de usuario y conexión entre interfaz gráfica y lógica en C++.

---

## Ejercicio 07 - Login con clima y fondo dinámico

Aplicación de login con QtDesigner que incorpora consumo de API externa para mostrar clima actual y hora local.
Incluye descarga dinámica de imágenes, caché local, soporte offline, logging de eventos y una ventana principal estilo perfil profesional.

---

## Ejercicio 08 - Editor multilenguaje

Editor de código desarrollado en Qt con soporte para C++, Python y Java.
Implementa herencia, polimorfismo, validación de sintaxis, redefinición de eventos de Qt y exportación del código a imagen JPG.

---

## Ejercicio 09 - Pintura con persistencia SQLite

Aplicación de dibujo libre desarrollada con Qt y SQLite.
Permite iniciar sesión con usuarios almacenados en base de datos, dibujar a mano alzada, modificar color y grosor de los trazos, deshacer acciones y reconstruir automáticamente el dibujo a partir de las coordenadas almacenadas.

---

## Ejercicio 10 - T-Rex Extremo

Juego inspirado en el clásico T-Rex de Google Chrome.
Incluye obstáculos dinámicos, pájaros con `QTimer` independiente, detección de colisiones, aumento progresivo de velocidad y reinicio de partida.

---

# Tecnologías utilizadas

- C++
- Qt Widgets
- Qt Designer
- Signals & Slots
- QNetworkAccessManager
- SQLite
- MySQL
- Qt SQL
- JSON / CSV
- Python
- Flask / FastAPI
- VPS Linux
- Git y GitHub

---

# Organización del repositorio

Cada ejercicio incluye, según corresponda:

- Código fuente
- Capturas de pantalla
- Recursos gráficos
- Archivos de datos
- Multimedia (videos explicativos cuando corresponda)
- README individual con explicación del proyecto

---

# Autor

**Avril Ogas**  
Estudiante de Ingeniería en Informática
