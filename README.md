# 📚 Programación Orientada a Objetos - Trabajos Prácticos

Repositorio correspondiente a la materia **Programación Orientada a Objetos**, donde se desarrollan distintos ejercicios prácticos utilizando **C++ y Qt**.

El objetivo general del repositorio es organizar en una misma rama principal todos los trabajos realizados durante la cursada, separados por carpetas y documentados individualmente.

---

## 📁 Estructura del repositorio

```text
Repositorio-Ogas-Avril-POO/
│
├── Ejercicio01/
├── Ejercicio02/
├── Ejercicio03/
├── Ejercicio04/
├── Ejercicio05/
├── Ejercicio06/
├── Ejercicio07/
└── README.md
````

---

## 🧩 Ejercicios

### 📌 Ejercicio 01 - Planificador de trabajos prácticos

Aplicación de escritorio desarrollada en Qt para organizar trabajos prácticos.
Incluye login con usuarios locales, persistencia de sesión por tiempo limitado, tablero de tareas en grilla, filtros por estado y prioridad, alta, edición y eliminación de trabajos, editor de notas e historial de acciones.

---

### 📌 Ejercicio 02 - Panel de monitoreo VPS

Aplicación Qt que funciona como panel de monitoreo de un servidor VPS.
Consume un endpoint HTTP que devuelve datos de salud del servidor, como estado general, uptime, carga, memoria y disco. La interfaz muestra métricas principales, último chequeo, historial de eventos, refresco manual y configuración de umbrales o intervalos.

---

### 📌 Ejercicio 03 - Lienzo colaborativo en tiempo real

Aplicación de dibujo colaborativo en Qt.
Permite dibujar a mano alzada sobre un lienzo usando `paintEvent`, con suavizado del trazo, interpolación de puntos, selección de color mediante teclas numéricas y control del grosor con la rueda del mouse. El dibujo se sincroniza con un backend en VPS para permitir colaboración entre usuarios.

---

### 📌 Ejercicio 04 - Tablero Kanban colaborativo

Aplicación de escritorio Qt para gestionar tareas tipo Kanban utilizando una API desarrollada con FastAPI y persistencia en MySQL.
Permite crear, editar y eliminar columnas y tarjetas, mover tarjetas entre columnas, reordenarlas y mantener actualizado el tablero mediante polling o WebSocket.

---

### 📌 Ejercicio 05 - Login sin QtDesigner

Aplicación de login desarrollada en un proyecto vacío de Qt, sin utilizar QtDesigner.
La interfaz se construye manualmente desde código, permitiendo comprender la creación de widgets, layouts, señales y slots de forma programática.

---

### 📌 Ejercicio 06 - Login con QtDesigner

Aplicación de login desarrollada utilizando QtDesigner.
El objetivo es trabajar con formularios visuales `.ui`, conectar los widgets con código C++ y validar el ingreso de usuario mediante señales y slots.

---

### 📌 Ejercicio 07 - Login con clima y fondo de pantalla

Aplicación de login con QtDesigner que incorpora consumo de API externa para mostrar el clima actual de Córdoba y la hora local.
Incluye validación de usuario, bloqueo temporal tras intentos fallidos, descarga de imagen de fondo con caché local, soporte para proxy, modo offline con datos simulados, registro de eventos y apertura de una ventana principal con currículum estilo LinkedIn.

---

## ⚙️ Tecnologías utilizadas

* C++
* Qt Widgets
* QtDesigner
* QNetworkAccessManager
* Signals y Slots
* JSON / CSV
* Python
* Flask / FastAPI
* MySQL
* VPS
* Git y GitHub


---

## 👩‍💻 Autor

Avril Ogas
Ingeniería en Informática

```

Así queda más claro qué contiene cada carpeta sin hacer el README principal demasiado largo.
```

