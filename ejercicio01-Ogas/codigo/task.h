#ifndef TASK_H
#define TASK_H

#include <QString>

/*
 * Clase: Task
 * ----------------------------
 * Representa un trabajo práctico dentro del sistema.
 * Guarda la información principal de cada tarea:
 * título, materia, fecha de entrega, estado y prioridad.
 */
class Task
{
private:
    // Identificador único del trabajo práctico
    int id;

    // Título o nombre del trabajo práctico
    QString titulo;

    // Materia a la que pertenece el trabajo práctico
    QString materia;

    // Fecha límite de entrega
    QString fechaEntrega;

    // Estado actual: Pendiente, En progreso o Entregado
    QString estado;

    // Prioridad del trabajo práctico: Alta, Media o Baja
    QString prioridad;

public:
    // Constructor por defecto
    Task();

    // Constructor con todos los datos necesarios para crear una tarea
    Task(int id, QString titulo, QString materia, QString fechaEntrega, QString estado, QString prioridad);

    // Métodos get: permiten consultar los datos de la tarea
    int getId() const;
    QString getTitulo() const;
    QString getMateria() const;
    QString getFechaEntrega() const;
    QString getEstado() const;
    QString getPrioridad() const;

    // Métodos set: permiten modificar los datos de la tarea
    void setId(int id);
    void setTitulo(const QString &titulo);
    void setMateria(const QString &materia);
    void setFechaEntrega(const QString &fechaEntrega);
    void setEstado(const QString &estado);
    void setPrioridad(const QString &prioridad);
};

#endif // TASK_H