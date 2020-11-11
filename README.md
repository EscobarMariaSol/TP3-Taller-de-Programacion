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

Para la resolución de este trabajo práctico se comenzó identificando todas las 
posibles partes del programa, para luego comenzar a implementar una solución 
parcial, orientada a cada parte identificada.
A continuación se detallarán las partes detectadas y las clases que se crearon 
para poder cubrir el comportamiento esperado.

### Protocolo Http

Esta parte del trabajo práctico encapsula todo el comportamiento referido a la 
identificación y resolución de las request incluidas en los petitorios 
recibidos desde los clientes. 
Se crea una clase HttpProtocol que recibirá el petitorio que a su vez ha sido 
recibido por el servidor, aquí se extraerá la request y el body, si es que este 
existe, para hacer esto se utiliza una clase llamada Parser que se encarga de 
leer el petitorio y extraer el método y recurso a utilizar. Una vez se obtiene 
el método y el recurso se hace uso de la clase Checker, que se encarga de 
verificar los métodos y recursos, de esta manera se decide qué tipo de 
respuesta, del tipo Response, se devolverá al servidor para ser enviada al 
cliente.

### Sockets

Para realizar esta parte del trabajo, se decidió implementar una clase Socket, 
la cual es utilizada tanto por el Servidor, Cliente y ThreadClient. Esta clase 
se encarga de conectar a la clase con el puerto y host correspondiente (si 
corresponde). Para no sobrecargar a dicha clase con el manejo de structs, que 
corresponden a las direcciones disponibles para cada puerto y host, las cuales 
son producto del llamado a la función *getaddrinfo(...)*, se decide crear una 
clase llamada HandleAddrinfo, que almacena las direcciones y se encarga de 
realizar las operaciones relacionadas con los *struct addrinfo*, desligando 
así completamente al socket de tener que inicializar, obtener o recorrer 
estas direcciones para conectarse.

### Cliente

La parte correspondiente al cliente fue una de las más simples de implementar, 
el mismo simplemente inicia su ejecución, conectandose al servidor, y espera 
a recibir un petitorio por entrada estándar, para hacer esto se delega esta 
responsabilidad sobre la clase IOHandler, que se encarga de recibir el 
petitorio y amacenarlo en un buffer. Luego de recibido el petitorio el cliente 
lo envia al servidor y espera la respuesta. Cuando recibe la respuesta le 
informa al IOHandler que la muestre por pantalla y termina la ejecución.

### Servidor

Esta parte de la resolución ha sido la más compleja, tanto para su 
implementación como para su modelado. El modelo utilizado para esta parte 
del trabajo consta de una clase ServerProgram, la cual recibe el puerto al 
cual debe conectarse y el archivo root del servidor. Lo primero que hace es 
utilizar a la clase IOHandler para leer el archivo root, y luego almacenar 
su contenido dentro del repositorio de recursos, este respositorio es una 
clase llamada Resourcer y es compartida por todos los threads que se ejecutan 
desde el servidor. 

Una vez se haya guardado el recurso root, se crea un thread, el cual está 
encapsulado dentro de la clase Servidor, a este se le delega la responsabilidad 
de despachar a los clientes, mientras este thread se ejecuta, el thread principal 
espera por entrada estándar el ingreso de la letra 'q' para finalizar la 
ejecución del programa y liberar los recursos.

Como se mencionó, el thread Servidor es el encargado de despachar a los clientes 
que vayan conectandose al servidor. Para hacer esto con una lista de clientes en 
la cual va guardando a los clientes conectados, cada conexión con un cliente se 
representa con la clase ThreadClient. Cada vez que despacha un cliente, revisa 
la lista de clientes conectados para liberar los recursos de los clientes que 
ya hayan finalizado su ejecución.

Finalmente tenemos a la clase ThreadClient, la cual es la encargada de manejar 
la comunicación con el cliente. En esta clase se recibe un cliente, luego se 
espera por el petitorio que el cliente enviará. Una vez recibido el petitorio 
se los procesa a través del HttpProtocol y se recibe una respuesta del tipo 
Response, esta respuesta se traduce a texto y se la envía al cliente. Previo a 
enviar la respuesta, se muestra por salida estándar el formato de la request 
recibida. Una vez enviada la respuesta el thread cierra la comunicación y 
finaliza su ejecución.

### Threads

Como se mencionó previamente, se utilizan threads tanto para manejar la 
recepción de nuevos clientes, clase Server, como para maneja la comunicación 
con dichos clientes, clase ThreadClient.

Para implementar los threads, se crea una clase abstracta Thread, que es de la 
cual heredan tanto Server como ThreadClient, ambos adquieren de esta la 
obligación de implementar el método run() y stop(), que permite lanzar la 
ejecución específica para cada thread y también detener la misma cuando sea 
necesario, de manera ordenada y liberando todos los recursos utilizados.

### Detección de las critical sections

En este trabajo práctico se ha detectado una única critical section, la cual 
corresponde al uso del repositorio de recursos compartidos, como se mencionó 
el servidor tiene la capacidad de dar de alta nuevos recursos y consultar los 
existentes. Los recursos se almacenan en un repositorio que es compartido por 
todos los threads, por lo que se ha hecho uso de un mutex, para proteger las 
operaciones que se pueden realizar sobre el mismo, impidiendo que un hilo 
pueda corromper la acción de otro hilo y cayendo así em comportamiento 
indeterminado, por parte del servidor.

### Excepciones

Para lidiar con los errores que puedan surgir a lo largo de la ejecución, 
tanto del lado del servidor como del cliente, se ha hecho uso de exepciones, 
más particularmente, se lanza una excepción del tipo *runtime_error* cuando 
se detecta justamente un error de ejecución, a las mismas se les asigna un 
mensaje que informa acerca del error ocurrido. Estas excepciones son atrapadas
donde se ha considerado que era apropiado, para el cliente lo hace en el mismo 
método donde se ejecuta la lógica principal, para el servidor se han atrapado 
las excepciones en diferentes estapas de la ejecución, donde se ha considerado 
que el hecho de no atrapar una excepción podría llevar a la pérdida de recursos.

Cuando una excepción es atrapada, generalmente se informa del error consultando 
el mensaje incluido en el mismo, a no ser que se trate de un error que no 
dependa exclusivamente de la implementación, sino que sea proveniente del uso 
de implementaciones de terceros, en ese caso simplemente se informa que se ha 
dado un error desconocido.

### Diagramas

A continuación se puede observar un diagrama de cómo se ha percibido el flujo 
principal del programa en conjunto cliente-servidor. Este diagrama intenta 
reflejar el flujo del programa a alto nivel, sin caer en demasiados detalles, 
pero explicando cómo se ha abordado la solución al requerimiento planteado.

##### Diagrama de Flujo Principal
![Flujo](https://github.com/EscobarMariaSol/TP3-Taller-de-Programacion/blob/main/img/TP3-Flujo.png)

Por otro lado se puede ver también el diagrama de clases, el cual es mucho más 
detallado. Allí se reflejan todas las clases implementadas, juntos con sus 
métodos y atributos, las relaciones entre las mismas y el tipo de relación.

##### Diagrama de Clases
![Clases](https://github.com/EscobarMariaSol/TP3-Taller-de-Programacion/blob/main/img/TP3-Clases.png)


## Clases implementadas

A continuación se detallará un poco más acerca de las interfaces implementadas 
para cada una de las clases creadas, explicacando brevemente el proqué de dicha 
implementación.
En caso de buscar una explicación más detallada, se puede consultar la 
documentación existente en cada uno de los archivos de cabecera.

### HttpProtocol

Esta clase, como se mencionó previamente, es la que se encarga de procesar 
los petitorios que recibe el servidor, extrayendo la request correspondiente 
y devolviendo una respuesta a la misma. La clase se instancia pasandole una 
referencia al repositorio de recursos compartido, logrando así que todos los 
pedidos de los clientes se manejen sobre el mismo petitorio.

La interfaz completa, que posee esta clase es la siguiente:
```C++
class HttpProtocol{
private:
    Resourcer& resourcer;
    Response* handlePostRequest(const Checker& checker, const Parser& parser,
        const std::pair<std::string, std::string>& line);
    Response* handleGetRequest(const Checker& checker, 
        const std::pair<std::string, std::string>& line);

public:
    explicit HttpProtocol(Resourcer& resourcer);
    ~HttpProtocol();
    Response* handleRequestResponse(const std::string& content);
    std::stringbuf getRequestFormat(const std::string& request) const;
};
```
Cuenta con un único atributo correspondiente al repositorio de recursos. Además 
cuenta con dos métodos privados, a los cuales se les delega la responsabilidad 
de procesar la request según si es un POST o GET, estos métodos se implementaron 
privados porque sólo son utilizados dentro de la clase, desde el método 
*handleRequestResponse(...)*.

### Checker

Esta es una clase fue implementada con el único propósito de chequear los tipos 
de request y recursos, desligando así a la clase HttpProtocol de realizar todos 
los chequeos. La clase se instancia recibiendo un par del tipo (método, recurso), 
que son los que utilizará para realizar todos los chequeos.

La interfaz completa de esta clase es la siguiente:
```C++
class Checker {
private:
    std::pair<std::string, std::string> request;
    bool isAGet() const;

public:
    explicit Checker(const std::pair<std::string, std::string>& request);
    ~Checker();
    bool isAValidMethod() const;
    bool isAPost() const;
    bool isRootResource() const;
};
```
Cuenta con un único atributo correspondiente a la request. Posee un método 
privado, el cual sólo es utilizado al momento de chequear si es un método 
válido en la función *isAValidMethod(...)*.

### Parser

Esta es la clase encarganda de parsear un petitorio, extrayendo la request 
y el body, si esta contiene uno, ignorando todo el resto del contenido que 
viene incluido dentro del petitorio. La clase se instancia pasandole un 
texto correspondiente a un petitorio.

La interfaz completa que posee la clase es la siguiente:
```C++
class Parser {
private:
    const std::string& content;
    std::string getResourceName() const;
    std::string getMethodName() const;

public:
    explicit Parser(const std::string& content);
    ~Parser();
    std::pair<std::string, std::string> parseRequest() const;
    std::string parseResourceValue() const;
};
```
La clase cuenta con un único atributo correspondiente al contenido del 
petitorio que se debe parsear. Posee dos métodos privados que sólo se utilizan 
dentro de la misma clase, en el método *parseRequest(...)*, las mismas surgen 
como un recurso para quitar un poco de responsabilidad al método mencionado.

### Resoucer

Clase correspondiente al repositorio donde se almacenan los recursos que los 
clientes pueden agregar/modificar o consultar. Esta clase es compartida por todos los threads que se crean desde el servidor, por lo cual cuenta con un 
atributo correspondiente al mutex que se encarga de proteger la ejecución de 
los métodos, evitando que se pueda corromper algún recurso o acción de un hilo 
desde otro hilo.

La interfaz completa de esta clase es la siguiente:
```C++
class Resourcer {
private:
    std::map<std::string, std::string> resources;
    std::mutex mutex;
    
public:
    Resourcer();
    ~Resourcer();
    Resourcer(const Resourcer& other);
    Resourcer& operator=(const Resourcer& other);
    void addResource(const std::string& resource_name, const std::string& resource_value);
    std::string getResourceValue(const std::string& resource_name);
    bool containsResource(const std::string& resource_name);
};
```
Vemos que cuenta con dos atributos, uno correspondiente al mutex ya mencionado 
y otro es el contenedor *map* donde se almacenan los recursos. Se puede 
observar que cuenta con un constructor y un operador asignación, ambos son por 
referencia, permitiendo así que exista una única instancia de la clase y que 
sea compartida por referencia entre todos los threads.

### Response

Esta clase intenta representar el comportamiento de una interfaz, ya que no es 
instancia da en ningún momento, ni posee implementación del único método que 
posee, el cual debe ser implementado por las clases que hereden de Response. 
Como tenemos cuatro tipos de respuestas posibles y algunas poseen un valor y 
otras no, se ha decidido que cada tipo de respuesta sean un tipo Response, así 
todas pueden ser consultadas a través del mismo método, sin necesidad de 
especificar su tipo exacto.

La interfaz completa de esta clase es la siguiente:
```C++
class Response {
public:
    Response();
    virtual ~Response();
    virtual void getResponse(std::stringbuf& str_serialize) = 0;
};
```
Como se puede ver cuenta con un único método, el cual es virtual puro, obligando 
asi a las clases que hereden de ella a implementar este método y así lograr 
que todas puedan comportarse como una Response.

A continuación se detalla la interfaz de cada una de las respuestas 
implementadas, nótese como todas cuentan con el mismo método heredado de la 
clase Response, al cual se le hace un override en cada clase.

##### OK

Corresponde a la respuesta *HTTP/1.1 200 OK* que se devuelve cuando la request 
se logra ejecutar correctamente. La clase cuenta con un atributo que 
corresponde con el valor del body del recurso, agregado o consultado.
```C++
class Ok: public Response {
private: 
    std::string value;

public:
    explicit Ok(const std::string& value);
    ~Ok();
    void getResponse(std::stringbuf& str_serialize) override;
};
```

##### Forbidden

Corresponde a la respuesta *HTTP/1.1 403 FORBIDDEN* que se devuelve cuando 
se intenta hacer un POST sobre el recurso root.
```C++
class Forbidden: public Response {
public:
    Forbidden();
    ~Forbidden();
    void getResponse(std::stringbuf& str_serialize) override;
};
```

##### NotFound

Corresponde a la respuesta *HTTP/1.1 404 NOT FOUND* que se devuelve cuando la 
request incluye un GET de un recurso que no existe en el repositorio.
```C++
class NotFound: public Response {
public:
    NotFound();
    ~NotFound();
    void getResponse(std::stringbuf& str_serialize) override;
};
```

#### NotAllowed

Corresponde a la respuesta *HTTP/1.1 405 METHOD NOT ALLOWED* que es la respuesta 
devuelta cuando se intenta utilizar un método que no es GET ni POST. La clase 
cuenta con un atributo correspondiente al nombre del método que se ha intentado 
utilizar.
```C++
class NotAllowed: public Response {
private:
    std::string value;
    
public:
    explicit NotAllowed(const std::string& value);
    ~NotAllowed();
    void getResponse(std::stringbuf& str_serialize) override;
};
```

### IOHandler

Clase encargada de interactuar con la entrada y salida estándar de datos, tanto 
dentro del servidor como en el cliente. La clase cuenta con una sobrecarga del 
constructor ya que la misma se puede instanciar pasandole la ruta de un archivo 
o sin ninguna ruta, haciendo así que tome como entrada la entrada estándar, para 
el caso da la salida de datos, siempre se utiliza la salida estándar.

La interfaz completa de esta clase es la siguiente:
```C++
class IOHandler {
private:
    std::fstream file;
    
public:
    IOHandler();
    explicit IOHandler(const std::string& path);
    ~IOHandler();
    void getInput(std::stringbuf& buffer);
    void setOutput(const std::stringbuf& msg);
    void getChar(char& c);
};
```
Posee un único atributo que corresponde al archivo desde el cual se leeran datos, 
si este existe. 

### Client

Clase correspondiente a un cliente que se conecta aun servidor, luego recibe un 
petitorio por entrada estándar y lo envia al servidor, espera respuesta, la 
muestra por salida estándar y finaliza su ejecución. La clase se instancia 
pasandole un host y un puerto, correspondiente al servidor al cual se 
quieren conectar.

La interfaz completa de esta clase es la  siguiente:
```C++
class Client {
private:
    Socket socket;
    IOHandler handler;
    void sendRequest(const std::stringbuf& buffer);
    void recvResponse(std::stringbuf& buffer);
    
public:
    Client(const char* host, const char* port);
    ~Client();
    void run();
};
```
Se puede ver que cuenta con dos atributos, uno correspondiente all Socket que 
se utilizará para establecer la comunicación con el servidor y el IOHandler 
que se encarga de recibir y devolver los datos correspondientes por salida o 
entrada estándar. Se puede ver tambien que cuenta con dos métodos privados, 
los cuales son utilizados dentro del método *run()*, uno se encarga de enviar 
un mensaje al servidor y luego cerrar el canal de comunicación de escritura, y 
el otro recibe un mensaje del servidor y luego cierra el canal de comunicación 
de lectura.

### ServerProgram

Clase correspondiente al Server principal, se encarga de conectar al servidor 
a un puerto y guardar el archivo root del servidor, luego delega la ejecución 
o otro hilo, servidor, y espera hasta que recibe una 'q' por entrada estándar, 
en ese momento detiene la ejecución y libera sus recursos. La clase se instancia 
recibiendo el puerto al cual se conectará y la ruta del archivo root.

La interfaz completa de esta clase es la siguiente:
```C++
class ServerProgram {
private:
    Resourcer resourcer;
    void saveRoot(IOHandler& io_handler);
    void stopServer(Server *server);
    
public:
    ServerProgram();
    ~ServerProgram();
    void startRunning(const char *port, const std::string& path);
};
```
Cuenta con un único atributo correspondiente al repositorio compartido ene el 
cual se guardan los recursos creados/accedidos por los clientes. Vemos que 
cuenta además con dos métodos privados, uno que se encarga de guardar el 
body del servidor en el repositorio y el otro es el encargado de indicar 
al thread servidor que debe detener su ejecución, ambos métodos son accedidos 
unicamente desde el *método startRunning(...)*.

### Thread

Esta clase es la encargada de lanzar los threads, tanto correspondiente al 
servidor como a los threads que representan la comunicación con el cliente, 
los cuales heredan este comportamiento de esta clase. Esta clase no se 
instancia en ningun momento, por lo que es una clase abstracta.

La interfaz completa de esta clase es la siguiente:
```C++
class Thread {
private:
    std::thread thread;
   
public:
    Thread();
    virtual ~Thread();
    void start();
    void join();
    virtual void run() = 0;
    virtual void stop() = 0;
    Thread(const Thread& other) = delete;
    Thread& operator=(const Thread& other) = delete;
    Thread(Thread&& other);
    Thread& operator=(Thread&& other);
};
```
La clase cuenta con un único atributo correspondiente al thread que se lanzará.
Vemos que los métodos *run()* y *stop()* son virtuales puros, por lo que deben 
ser implementados por cada clase que herede de thread. Por otro lado se puede ver 
que de han borrado tando el constructor por copia como el operador asignación por
copia, impidiendo así que se realice una copia del thread, estos son reemplazados 
por el constructor y operador asignación por movimiento, es cual mueve un thread 
de un objeto a otro, inhabilitando el thread del objeto anterior.

### Server

Clase correspondiente al thread servidor, es el encargado de recibir a los 
nuevos clientes que se vayan conectando y "despacharlos" a través de otro 
thread que se encargará de manejar la comunicación. Esta clase se mantiene 
en ejecución hasta que el programa servidor le indique que debe detenerse.
La clase se instancia recibiendo el puerto en el cual escuchará a los 
nuevos clientes y el repositorio de recursos que será compartido por todos 
los threads de clientes.

La interfaz completa de esta clase es la siguiente:
```C++
class Server: public Thread {
private:
    Socket socket;
    Resourcer& resourcer;
    std::atomic<bool> keep_running;
    void addClients(std::list<ThreadClient*>& clients);
    void cleanClients(std::list<ThreadClient*>& clients);
    void stopAndCleanClients(std::list<ThreadClient*>& clients);

public:
    Server(const char *port, Resourcer& resourcer);
    ~Server();
    void run() override;
    void stop() override;
};
```
La clase cuenta con un atributo socket, correspondiente al socket a través 
del cual el servidor escuchará a los nuevos clientes, otro denominado resourcer, 
corresponde al repositorio en el cual están almacenados los recursos que serán 
accedidos/ modificados segun los petitorios que se reciban de los clientes y otro 
denominado keep_running, un booleano que indica si el server debe seguir su 
ejecución o detenerse y liberar los recursos utilizados, ordenadamente.
Podemos ver además que se está haciendo override de los métodos heredados de la 
clase Thread, definiendo así el comportamiento que tendrán para esta clase en 
específico. Y finalmente observamos que hay 3 métodos privados que corresponden 
a la adición, limpieza y finalización de los clientes, los cuales son invocados 
desde el método *run()*.

### ThreadClient

Esta clase es la correspondiente a la conexión de cada cliente. Por cada cliente 
que se conecta al servidor se crea una nueva instancia de esta clase. Como el 
nombre lo indica, esta clase hereda de Thread, pues cada conexión con un cliente 
será un thread nuevo, permitiendo así el despacho en "simultaneo" de diferentes 
clientes. La calse se instancia recibiendo un Socket que conectará con el cliente
y el repositorio que será accedido a través del protocolo que maneja los petitorios 
http que envian los clientes.

La interfaz completa de esta clase es la siguiente:
```C++

class ThreadClient: public Thread {
private:
    Socket peer;
    Resourcer& resourcer;
    std::atomic<bool> running;
    void recvRequest(std::stringbuf& request);
    void sendResponse(Response *response);

public:
    ThreadClient(Socket&& peer, Resourcer& resourcer);
    ~ThreadClient();
    void run() override;
    void stop() override;
    bool hasFinished() const;
};
```
Como se ve, la clase cuenta con los atributos peer, que corresponde al socket 
a través del cual establecera comunicación con el cliente, resourcer, 
corresponde al repositorio en el cual están almacenados los recursos que serán 
accedidos/ modificados segun los petitorios de clientes y running, corresponde a 
un booleano, que indica si el thread aún sigue ejecutandose o ya terminó.
Cuenta con dos métodos privados, bastante similar a la interfaz vista en el 
cliente, un método recibe el petitorio del cliente y el otro envía la respuesta 
a dicha request, estos métodos son invocados desde el método principal *run()*, 
el cual es heredado de Thread. Vemos que también hace un override del método 
*stop()* y *run()* como lo requiere la herencia con la clase Thread.

### Socket

Esta clase corresponde al socket a través del cual se establece la 
comunicación entre el cliente y el servidor. La misma se puede instanciar 
de diferentes maneras, pues cuenta con una sobrecarga del constructor 
lo cual permite diferenciar la creación de un socket cliente, servidor o 
peer. Para instanciar un cliente recibe un host y un puerto, 
correspondientes al servidor al cual se quieren conectar, para el servidor 
se recibe unicamente un puerto, correspondiente al puerto en el cual 
escuchará, y finalmente para instanciar un peer se recibe únicamente 
el file descriptor del mismo.

La interfaz completa de esta clase es la siguiente:
```C++
class Socket {
private:
    int fd;
    explicit Socket(const int& fd);
    void setFileDescriptor(const HandlerAddrinfo& addrinfo);
    void bindAndListen(HandlerAddrinfo& addrinfo);
    void activeReuseAddress();
    
public:
    Socket(const char* host, const char* port);
    explicit Socket(const char *port);
    Socket(const Socket& other) = delete;
    Socket& operator=(const Socket& other) = delete;
    Socket(Socket&& other);
    Socket& operator=(Socket&& other);
    ~Socket();
    Socket accept();
    int send(const char *buffer, const size_t size);
    int recv(char *buffer, const size_t size);
    void shutdown(int channel);
    void close();
};
```
Esta es una de las clases más sobrecargadas dentro del modelo de resolución 
implementado. Inicialmente se ve que cuenta con sobrecarga de constructores, 
como se menciono previamente, pero se debe notar que uno de los constructores 
es privado, esto es porque el mismo corresponde al constructor de un peer, el 
cual únicamente es invocado dentro de la misma clase, a la hora de hacer un 
accept, esta maniobra evita que se pueda instanciar un socket pasandole un 
valor de file descriptor inválido. Vemos también que se han borrado tanto el 
constructor y el operador asignación por copia y se los ha reemplazado por 
los de movimiento, impidiendo así la copia innecesaria de datos y además 
evitando la pérdida o corrupción de los datos. 
Se puede ver que cuenta además con unos métodos privados, estos se utilizan 
desde el constructor del servidor, para realizar la correcta conexión del mismo.

### HandlerAddrinfo

Como ya se ha mencionado, esta clase se encarga de manejar todo lo relacionado 
a direcciones del tipo *struct addrinfo*, abtrayendo así al Socket de tener que 
realizar operaciones como recorrer estas direcciones para obtener un file 
descriptor válido. La calse se instancia con el valor de un flag, que se 
utiliza para inicializar la estructura de direcciones que tiene como atributo, 
la cual se ha denominado *hints*, este flag difiere la manera en que se 
inciliza un cliente y un servidor

```C++
class HandlerAddrinfo {
private:
    struct addrinfo hints;
    struct addrinfo *addr;
    void init(const int flag);

public:
    explicit HandlerAddrinfo(const int flag);
    ~HandlerAddrinfo();
    void callGetAddrinfo(const char* host, const char* port);
    int openSocket() const;
    void bindAddress(const int fd);
    void connectAddress(int& fd);
};
```
La clase cuenta con dos atributos, que corresponde a las direcciones que se 
inicializarán y se utilizarán para establecer los valores de file descriptor 
que se utilizarán para establecer las conexiones entre el servidor y los 
clientes. Cuenta con un método privado para inicializar el atributo *hints*,
que se utilizará en el llamado a *getaddrinfo(...)*, el cual devuelve el file 
descriptor asignado al socket.