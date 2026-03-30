#ifndef TASK_H
#define TASK_H

#include <QString>

class Task
{
private:
    int id;
    QString titulo;
    QString materia;
    QString fechaEntrega;
    QString estado;
    QString prioridad;

public:
    Task();
    Task(int id, QString titulo, QString materia, QString fechaEntrega, QString estado, QString prioridad);

    int getId() const;
    QString getTitulo() const;
    QString getMateria() const;
    QString getFechaEntrega() const;
    QString getEstado() const;
    QString getPrioridad() const;

    void setId(int id);
    void setTitulo(const QString &titulo);
    void setMateria(const QString &materia);
    void setFechaEntrega(const QString &fechaEntrega);
    void setEstado(const QString &estado);
    void setPrioridad(const QString &prioridad);
};

#endif // TASK_H