#include "task.h"

Task::Task()
{
    id = 0;
}

Task::Task(int id, QString titulo, QString materia, QString fechaEntrega, QString estado, QString prioridad)
{
    this->id = id;
    this->titulo = titulo;
    this->materia = materia;
    this->fechaEntrega = fechaEntrega;
    this->estado = estado;
    this->prioridad = prioridad;
}

int Task::getId() const
{
    return id;
}

QString Task::getTitulo() const
{
    return titulo;
}

QString Task::getMateria() const
{
    return materia;
}

QString Task::getFechaEntrega() const
{
    return fechaEntrega;
}

QString Task::getEstado() const
{
    return estado;
}

QString Task::getPrioridad() const
{
    return prioridad;
}

void Task::setId(int id)
{
    this->id = id;
}

void Task::setTitulo(const QString &titulo)
{
    this->titulo = titulo;
}

void Task::setMateria(const QString &materia)
{
    this->materia = materia;
}

void Task::setFechaEntrega(const QString &fechaEntrega)
{
    this->fechaEntrega = fechaEntrega;
}

void Task::setEstado(const QString &estado)
{
    this->estado = estado;
}

void Task::setPrioridad(const QString &prioridad)
{
    this->prioridad = prioridad;
}