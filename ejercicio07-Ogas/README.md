# Ejercicio 07 - Login con Clima y Fondo Dinámico

## Descripción

Aplicación desarrollada en C++ utilizando Qt Widgets que implementa un sistema de login con validación, consumo de API externa para obtener información climática y carga dinámica de imágenes.

El proyecto integra funcionalidades de red, manejo de archivos, soporte para proxy, persistencia local y diseño de interfaz gráfica mediante Qt Designer.

---

## Funcionalidades principales

- Login con validación de usuario
- Bloqueo temporal tras 3 intentos fallidos
- Consumo de API externa de clima
- Descarga dinámica de imágenes de fondo
- Caché local de imágenes
- Soporte para proxy HTTP
- Modo offline con datos simulados
- Registro de eventos en archivo de logs
- Apertura de ventana principal en pantalla completa
- Perfil profesional estilo LinkedIn

---

## Login

- Usuario: `admin`
- Contraseña: `1234`
- Validación de credenciales
- Mensajes de error amigables

---

## Consumo de API

Se utiliza la API de OpenWeatherMap para obtener el clima actual mediante consultas HTTP directas, sin utilizar SDKs externos.

### Datos obtenidos

- Temperatura actual
- Descripción del clima
- Hora local
- Estado climático

### Características

- Uso de API Key
- Procesamiento de respuestas JSON
- Configuración de ciudad y unidades métricas

---

## Proxy HTTP

La aplicación soporta conexión mediante proxy configurado sobre un VPS utilizando Tinyproxy.

```text
Aplicación Qt → Proxy VPS → API externa
```

Esto permite enrutar las solicitudes de red antes de acceder a la API externa.

---

## Imágenes dinámicas

- Descarga de imágenes desde URL pública
- Caché local
- Escalado manteniendo relación de aspecto
- Apertura de ventana principal solo luego de finalizar la descarga

---

## Ventana principal

La ventana principal se muestra en pantalla completa luego de un login válido.

Incluye un perfil profesional estilo LinkedIn con:

- Foto personal
- Nombre
- Descripción profesional
- Tecnologías y habilidades

---

## Arquitectura

El proyecto implementa una estructura orientada a objetos basada en herencia y abstracción:

- `Pantalla` → clase base abstracta
- `Login` → pantalla de autenticación
- `Ventana` → ventana principal
- `Clima` → manejo de datos y API

---

## Signals & Slots

Se utilizó el mecanismo de Qt para:

- Manejo de eventos de red
- Comunicación entre componentes
- Actualización dinámica de la interfaz

---

## Configuración

Archivo `config.txt`:

```txt
API_KEY=TU_API_KEY
CIUDAD=Cordoba,AR
PROXY_HOST=IP_DEL_VPS
PROXY_PORT=8888
```

---

## Modo Offline

Si la conexión falla o la API no responde:

- Se cargan datos simulados
- Se informa el estado al usuario mediante la interfaz

---

## Logs

Se registran eventos importantes en archivos de log:

- Intentos de login
- Errores
- Consultas a la API
- Descarga de imágenes
- Eventos de red

---

## Tecnologías utilizadas

- C++
- Qt Widgets
- Qt Designer
- QNetworkAccessManager
- JSON
- Tinyproxy
- VPS Linux
- Git y GitHub

---

## Estructura del proyecto

```text
ejercicio07-Ogas/
│
├── codigo/
├── capturas/
└── README.md
```

---

## Capturas

### Login

![Login](capturas/login.png)

### Ventana principal

![Ventana](capturas/ventana.png)

---

## Compilación y ejecución

1. Abrir el archivo `.pro` desde Qt Creator.
2. Configurar el kit de compilación.
3. Ejecutar el proyecto.

---

## Estado

✔ Ejercicio completado

---

## Autor

**Avril Ogas**  
Ingeniería en Informática