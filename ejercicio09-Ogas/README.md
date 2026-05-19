# Ejercicio 09 - Coordenadas en base de datos

Aplicación de escritorio desarrollada en C++ con Qt Widgets.  
El sistema permite iniciar sesión con usuarios almacenados en SQLite y acceder a un lienzo de dibujo a mano alzada. Cada trazo realizado se guarda en la base de datos mediante sus coordenadas, color y grosor, permitiendo reconstruir el dibujo al volver a abrir la aplicación.

## Funcionalidades principales

- Login construido con Qt Designer.
- Validación de usuarios contra una base SQLite.
- Registro de accesos exitosos e intentos fallidos en archivo de log.
- Lienzo de dibujo implementado con una clase `Pintura` derivada de `QWidget`.
- Dibujo libre con mouse.
- Cambio de grosor con la rueda del mouse.
- Cambio de color con teclas `R`, `G` y `B`.
- Borrado completo del lienzo con `Escape`.
- Deshacer hasta las últimas 10 acciones con `Ctrl + Z`.
- Persistencia de trazos y coordenadas en SQLite.
- Reconstrucción del dibujo al iniciar sesión nuevamente.

## Usuario de prueba

```txt
Usuario: admin
Contraseña: 1234
```

## Base de datos

La base utilizada es:

```txt
datos/dibujos.db
```

Tablas principales:

```txt
usuarios
trazos
coordenadas
```

## Estructura de tablas

```sql
CREATE TABLE usuarios (
    id_usuario INTEGER PRIMARY KEY AUTOINCREMENT,
    usuario TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL
);

CREATE TABLE trazos (
    id_trazo INTEGER PRIMARY KEY AUTOINCREMENT,
    id_usuario INTEGER NOT NULL,
    color TEXT NOT NULL,
    grosor INTEGER NOT NULL,
    fecha TEXT NOT NULL,
    FOREIGN KEY (id_usuario) REFERENCES usuarios(id_usuario)
);

CREATE TABLE coordenadas (
    id_coord INTEGER PRIMARY KEY AUTOINCREMENT,
    id_trazo INTEGER NOT NULL,
    x INTEGER NOT NULL,
    y INTEGER NOT NULL,
    orden_punto INTEGER NOT NULL,
    FOREIGN KEY (id_trazo) REFERENCES trazos(id_trazo)
);
```

## Controles del lienzo

| Acción                    | Control                       |
| ------------------------- | ----------------------------- |
| Dibujar                   | Click izquierdo + mover mouse |
| Aumentar/disminuir grosor | Rueda del mouse               |
| Color rojo                | Tecla R                       |
| Color verde               | Tecla G                       |
| Color azul                | Tecla B                       |
| Borrar lienzo             | Escape                        |
| Deshacer                  | Ctrl + Z                      |

## Clases principales

| Clase      | Responsabilidad                                                   |
| ---------- | ----------------------------------------------------------------- |
| `Login`    | Pantalla inicial diseñada con Qt Designer y validación de usuario |
| `Ventana`  | Ventana principal que contiene el lienzo                          |
| `Pintura`  | Widget de dibujo a mano alzada                                    |
| `Database` | Conexión, consultas y persistencia en SQLite                      |
| `Logger`   | Registro de eventos en archivo de log                             |

## Configuración del proyecto

El archivo `.pro` debe incluir:

```pro
QT += core gui widgets sql

CONFIG += c++17
```

## Ejecución

1. Abrir el proyecto en Qt Creator.
2. Verificar que exista la base `dibujos.db`.
3. Compilar el proyecto.
4. Iniciar sesión con el usuario de prueba.
5. Dibujar en el lienzo.
6. Cerrar y volver a abrir la aplicación para comprobar la reconstrucción del dibujo.

## Logs

Los accesos se registran en:

```txt
logs/accesos.log
```

Ejemplo:

```txt
[2026-05-19 18:30:10] ACCESO EXITOSO - usuario: admin
[2026-05-19 18:32:41] INTENTO FALLIDO - usuario: admin
```