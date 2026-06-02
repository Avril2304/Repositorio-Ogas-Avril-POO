#ifndef TASKFORMWIDGET_H
#define TASKFORMWIDGET_H

#include <QWidget>
#include "task.h"

class QLineEdit;
class QComboBox;
class QPushButton;

/*
 * Clase: TaskFormWidget
 * ----------------------------
 * Formulario reutilizable para crear o editar trabajos prácticos.
 * En modo alta genera una tarea sin ID definitivo; en modo edición conserva
 * el ID de la tarea recibida.
 */
class TaskFormWidget : public QWidget
{
    Q_OBJECT

private:
    // Tarea original y bandera que indica si el formulario está editando.
    Task currentTask;
    bool editMode;

    // Controles del formulario.
    QLineEdit *txtTitulo;
    QLineEdit *txtMateria;
    QLineEdit *txtFecha;
    QComboBox *cmbEstado;
    QComboBox *cmbPrioridad;
    QPushButton *btnGuardar;

private slots:
    // Valida los campos, arma la tarea y emite la señal taskSaved.
    void handleSave();

signals:
    // Señal enviada a MainWidget cuando se confirma el formulario.
    void taskSaved(Task task);

public:
    // Constructor para crear una tarea nueva.
    explicit TaskFormWidget(QWidget *parent = nullptr);

    // Constructor para editar una tarea existente.
    explicit TaskFormWidget(Task task, QWidget *parent = nullptr);
};

#endif // TASKFORMWIDGET_H
