# Ejercicio 08 - Editor Multilenguaje

## Descripción

Aplicación de escritorio desarrollada en C++ con Qt Widgets. El sistema implementa un login inicial, control de intentos fallidos, bloqueo temporal y un editor multilenguaje con validación sintáctica básica para C++, Python y Java.

El objetivo principal del ejercicio es aplicar herencia, clases abstractas, polimorfismo, redefinición de eventos, signals/slots y persistencia local mediante archivos.

## Usuario de prueba

```txt
Usuario: admin
Contraseña: 1234
````

Las credenciales del login se configuran desde el archivo:

```txt
datos/config.txt
```

## Funcionalidades principales

* Login inicial con usuario y contraseña.
* Bloqueo temporal luego de 3 intentos fallidos.
* Clase base abstracta `Pantalla`.
* Clases derivadas:

  * `Login`
  * `EditorPrincipal`
  * `ModoBloqueado`
* Uso de polimorfismo mediante punteros a `Pantalla`.
* Editor principal en pantalla completa.
* Selector de lenguaje:

  * C++
  * Python
  * Java
* Jerarquía polimórfica de validadores:

  * `ValidadorSintaxis`
  * `ValidadorCpp`
  * `ValidadorPython`
  * `ValidadorJava`
* Validación de sintaxis por línea.
* Resaltado de errores en rojo.
* Mensajes amigables en la interfaz.
* Redefinición de eventos:

  * `keyPressEvent`
  * `mousePressEvent`
  * `resizeEvent`
  * `closeEvent`
  * `focusInEvent`
  * `focusOutEvent`
* Registro de eventos en archivo de log.
* Lectura de configuración desde archivo.
* Exportación del código escrito a un archivo JPG.
* Panel lateral estilo LinkedIn con perfil personal.
* Funcionamiento offline, sin servicios remotos.

## Archivos de configuración

El archivo `config.txt` contiene:

```txt
usuario=admin
password=1234
tiempo_bloqueo=10
lenguaje_defecto=C++
ruta_exportacion=datos/codigo_exportado.jpg
```

## Registro de eventos

La aplicación guarda acciones importantes en:

```txt
datos/eventos.log
```

Ejemplos de eventos registrados:

```txt
Login correcto
Intento fallido de login
Usuario bloqueado temporalmente
Cambio de lenguaje
Error de sintaxis
Código exportado a JPG
Editor cerrado
```

## Exportación

El botón **Exportar a JPG** genera una imagen con todo el código escrito en el editor, respetando saltos de línea y numeración.

## Tecnologías utilizadas

* C++
* Qt Widgets
* Signals y Slots
* Archivos locales
* Programación Orientada a Objetos
* Herencia y polimorfismo