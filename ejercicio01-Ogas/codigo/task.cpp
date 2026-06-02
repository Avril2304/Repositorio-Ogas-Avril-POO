#include "task.h"

/*
 * Constructor por defecto.
 * Inicializa el identificador en 0.
 */
Task::Task()
{
    id = 0;
}

/*
 * Constructor parametrizado.
 * Recibe todos los datos de un trabajo práctico
 * y los asigna a los atributos de la clase.
 */
Task::Task(int id, QString titulo, QString materia, QString fechaEntrega, QString estado, QString prioridad)
{
    this->id = id;
    this->titulo = titulo;
    this->materia = materia;
    this->fechaEntrega = fechaEntrega;
    this->estado = estado;
    this->prioridad = prioridad;
}

 //Devuelve el identificador de la tarea.
int Task::getId() const
{
    return id;
}

//Devuelve el título de la tarea.
QString Task::getTitulo() const
{
    return titulo;
}

//Devuelve la materia asociada.
QString Task::getMateria() const
{
    return materia;
}

//Devuelve la fecha de entrega.
QString Task::getFechaEntrega() const
{
    return fechaEntrega;
}

//Devuelve el estado actual de la tarea.
QString Task::getEstado() const
{
    return estado;
}

//Devuelve la prioridad de la tarea.
QString Task::getPrioridad() const
{
    return prioridad;
}

//Modifica el identificador de la tarea.
void Task::setId(int id)
{
    this->id = id;
}

// Modifica el título de la tarea.
void Task::setTitulo(const QString &titulo)
{
    this->titulo = titulo;
}

//Modifica la materia asociada.
void Task::setMateria(const QString &materia)
{
    this->materia = materia;
}

//Modifica la fecha de entrega.
void Task::setFechaEntrega(const QString &fechaEntrega)
{
    this->fechaEntrega = fechaEntrega;
}

//Modifica el estado de la tarea.
void Task::setEstado(const QString &estado)
{
    this->estado = estado;
}

//Modifica la prioridad de la tarea.
void Task::setPrioridad(const QString &prioridad)
{
    this->prioridad = prioridad;
}