# Ejercicio 07 - Login con Clima y Fondo Dinámico

## Descripción

Aplicación desarrollada en C++ utilizando Qt Widgets que implementa un sistema de login con validación, consumo de API externa para obtener el clima actual y carga dinámica de imágenes.

El sistema integra funcionalidades de red, manejo de archivos, uso de proxy y diseño de interfaz gráfica.

---

## Login

- Usuario: `admin`
- Contraseña: `1234`
- Bloqueo temporal luego de 3 intentos fallidos
- Mensajes de error amigables

---

## Consumo de API

Se utiliza la API de OpenWeatherMap para obtener el clima actual.

- Consulta mediante HTTP (sin SDK)
- Uso de API Key
- Parámetros: ciudad y unidades métricas
- Procesamiento de respuesta JSON

Ejemplo de datos obtenidos:
- Temperatura
- Descripción del clima

---

## Proxy

La aplicación soporta conexión mediante proxy HTTP.

Se configuró un proxy en un VPS utilizando Tinyproxy.

Esto permite enrutar las solicitudes de red:

```

Aplicación Qt → Proxy VPS → API externa

```

---

## Imágenes

- Descarga de fondo dinámico desde URL pública
- Cache local de imágenes
- Imagen principal descargada antes de abrir la ventana principal
- Escalado manteniendo relación de aspecto (sin deformación)

---

## Ventana Principal

- Se abre solo tras login válido
- Se muestra en pantalla completa
- Contiene un CV estilo LinkedIn:
  - Foto
  - Nombre
  - Descripción profesional
  - Tecnologías

---

## Arquitectura

Se implementó una estructura orientada a objetos:

- `Pantalla` (clase base abstracta)
- `Login` (hereda de Pantalla)
- `Ventana` (hereda de Pantalla)
- `Clima` (manejo de datos y API)

---

## Signals & Slots

Se utilizó el mecanismo de Qt para:

- Manejo de eventos de red
- Comunicación entre clases
- Actualización de UI

---

## Configuración

Archivo `config.txt`:

```

API_KEY=TU_API_KEY
CIUDAD=Cordoba,AR
PROXY_HOST=IP_DEL_VPS
PROXY_PORT=8888

```

---

## Modo Offline

- Si falla la conexión o la API:
  - Se muestran datos simulados
  - Se informa al usuario mediante la UI

---

## Logs

Se registran eventos en archivo:

- Intentos de login
- Errores
- Consultas a la API
- Descarga de imágenes

---

## Tecnologías utilizadas

- C++
- Qt (Widgets)
- QNetworkAccessManager
- JSON
- Tinyproxy (VPS)
- Git & GitHub

---


### Login
![Login](capturas/login.png)

### Ventana principal
![Ventana](capturas/ventana.png)
```

