# Implementación del VPS y conexión al endpoint

## Descripción

Para este proyecto se utilizó un servidor VPS (Virtual Private Server) con el objetivo de simular un entorno real de monitoreo.

En el VPS se implementó un endpoint HTTP que devuelve información de salud del sistema en formato JSON. Este endpoint es consumido por la aplicación Qt para mostrar el estado del servidor.

---

## Datos del VPS

- Dirección IP: `161.97.92.143`
- Acceso: SSH
- Lenguaje utilizado: Python
- Framework: Flask

---

## Acceso al servidor

La conexión al VPS se realizó mediante SSH:

```bash
ssh lolo@161.97.92.143
```

## Configuración del entorno

Para trabajar de forma segura y sin afectar el sistema del VPS, se utilizó un entorno virtual de Python.

### Creación del entorno:
```bash
python3 -m venv venv
``` 
### Activación del entorno:
```bash
ssh source venv/bin/activate
```
### Una vez activado, se instaló Flask:
```bash
ssh pip install flask
```
---

## Implementación del endpoint

Se creó un archivo server.py que define un endpoint /health.

### Código del servidor

```Python
    load = os.getloadavg()[0]
    memory = 50

    status = "ok"
    if memory > 80 or disk_percent > 80:
        status = "alert"

    return jsonify({
        "status": status,
        "uptime": "Servidor activo",
        "load": round(load, 2),
        "memory": memory,
        "disk": disk_percent
    })

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
```
---

## Ejecución del servidor

El servidor se ejecuta con:

```bash
python server.py
```
Esto deja activo el endpoint en:

```bash
http://161.97.92.143:5000/health
```

---

## Configuración de red

Para permitir el acceso desde la aplicación, se habilitó el puerto:

```bash
sudo ufw allow 5000
```
---

## Conexión con la aplicación Qt

La aplicación Qt se conecta al endpoint mediante la URL:

```bash
http://161.97.92.143:5000/health
```
La comunicación se realiza utilizando QNetworkAccessManager, permitiendo enviar solicitudes HTTP y recibir la respuesta en formato JSON.


---
## Formato de respuesta
El endpoint devuelve un JSON con la siguiente estructura:

```JSON
{
  "status": "ok",
  "uptime": "Servidor activo",
  "load": 0.35,
  "memory": 50,
  "disk": 62
}
```
Estos datos son procesados por la aplicación para actualizar el estado y las métricas del panel.

## Consideraciones
- El servidor Flask se ejecuta en modo desarrollo, por lo que requiere mantener la terminal abierta.
- Si el servidor se detiene, la aplicación muestra estado CAÍDO.
- El uso de un entorno virtual permite aislar dependencias y mantener el sistema del VPS sin modificaciones.
---
