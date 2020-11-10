# Trabajo Práctico 3 - Taller de Programación I
# Informe de Resolución


**Nombre:**  Escobar Benitez Maria Soledad

**Padrón:**  97877

**Repositorio:** [Link GitHub!](https://github.com/EscobarMariaSol/TP3-Taller-de-Programacion)

**Fecha de entrega:** 13/11/2020


## Introducción

En este trabajo práctico se desarrollará una aplicación servidor que atenderá 
petitorios HTTP, mediante los cuales podrá acceder y dar alta a recursos del 
mismo.

### Comportamiento del Servidor

El servidor recibirá por parámetro el puerto TCP (o servicio) en el cual deberá
 escuchar las conexiones entrantes y un parámetro ​ <template_root>  que​ 
representa la ruta a un archivo con una respuesta para el recurso principal “/”.

##### Manejo de petitorios
El servidor deberá poder interpretar petitorios HTTP, y extraer de estos los
siguientes parámetros:
1. Método (GET, POST, etc)
2. Ruta del recurso
3. Body en caso de que corresponda
Utilizando estos parámetros deberá ejecutar la lógica correspondiente y 
devolver una respuesta también en formato HTTP.

##### Entrada y salida estándar
El servidor imprime por salida standard la primer linea del petitorio de 
cada cliente que va despachando. Al mismo tiempo esperará el caracter ​ ‘q’​ 
por entrada estándar, cuando lo reciba, el servidor deberá cerrar el socket 
aceptador, y esperar a que las conexiones se cierren antes de liberar los 
recursos y retornar.

##### Código de retorno
El servidor devolverá 0 si su ejecución fue exitosa. Si la cantidad de 
parámetros es incorrecta, se cancela la ejecución y se devuelve 1.

### Comportamiento del Cliente

El cliente se conectará al servidor corriendo en la máquina con dirección 
IP ​ <ip/hostname>​, en el puerto TCP ​ <puerto/servicio>​. 
Recibirá por entrada standard el texto correspondiente a un petitorio HTTP, el 
cuál leerá y enviará por socket hasta llegar a EOF. Una vez enviado el 
petitorio, escuchará la respuesta del servidor e imprimirá por salida standard.


## Esquema de resolución


### Protocolo



### Sockets



### Cliente


### Servidor



### Threads




### Detección de las critical sections


### Diagramas

![Flujo](https://github.com/EscobarMariaSol/TP2-Taller-de-Programacion/blob/main/img/TP3-Flujo.png)



![Clases](https://github.com/EscobarMariaSol/TP2-Taller-de-Programacion/blob/main/img/TP3-Clases.png)


## Clases implementadas

A continuación se detallará un poco más acerca de las interfaces implementadas 
para cada una de las clases creadas, explicacando brevemente el proqué de dicha 
implementación.
En caso de buscar una explicación más detallada, se puede consultar la 
documentación existente en cada uno de los archivos de cabecera.

### HttpProtocol

### Checker

### Parser

### Resoucer

### Response

### IOHandler

### Client

### ServerProgram

### Thread

### Server

### ThreadClient

### Socket

### HandlerAddrinfo

