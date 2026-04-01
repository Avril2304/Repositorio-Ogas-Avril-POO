#ifndef TASKFORMWIDGET_H
#define TASKFORMWIDGET_H

#include <QWidget>
#include "task.h"

class QLineEdit;
class QComboBox;
class QPushButton;

class TaskFormWidget : public QWidget
{
    Q_OBJECT

private:
    Task currentTask;
    bool editMode;

    QLineEdit *txtTitulo;
    QLineEdit *txtMateria;
    QLineEdit *txtFecha;
    QComboBox *cmbEstado;
    QComboBox *cmbPrioridad;
    QPushButton *btnGuardar;

private slots:
    void handleSave();

signals:
    void taskSaved(Task task);

public:
    explicit TaskFormWidget(QWidget *parent = nullptr);
    explicit TaskFormWidget(Task task, QWidget *parent = nullptr);
};

#endif // TASKFORMWIDGET_H