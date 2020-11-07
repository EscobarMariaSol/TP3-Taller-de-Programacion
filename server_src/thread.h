#ifndef COMMON_THREAD_H
#define COMMON_THREAD_H

#include <utility>
#include <thread>

// Clase encargada de crear un thread
// Cuenta con un único atributo correspondiente al thread que se lanzará
// para cada instacia 
class Thread {
private:
    std::thread thread;
   
public:
    // Constructor
    Thread();
    // Destructor
    virtual ~Thread();
    // Metodo que inicializa el atributo thread y llama al método
    // que debe ejecutar, run, pasandole una instancia de sí mismo.
    // Pos: el método run se ha ejecutado
    void start();
    // Método que realiza un join del thread al thread main
    // Pre: el atributo thread ha sido inicializado
    // Pos: el thread se ha unido al thread main.
    void join();
    // Método que se encarga de ejecutar el thread
    // el método es virtual puro, pues ha de ser implementado por las clases 
    // que hereden de Thread
    virtual void run() = 0;
    // Impide que se realice una copia del Thread
    Thread(const Thread& other) = delete;
    // Impide que se realice una asignación del Thread
    Thread& operator=(const Thread& other) = delete;
    // Constructor por movimiento
    Thread(Thread&& other);
    // Método que permite que se realice una asignación por movimiento
    Thread& operator=(Thread&& other);
};

#endif // COMMON_THREAD_H
