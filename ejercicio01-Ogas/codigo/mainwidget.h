#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QVector>
#include "task.h"

class QGridLayout;
class QComboBox;
class QListWidget;
class QPushButton;

/*
 * Clase: MainWidget
 * ----------------------------
 * Ventana principal del planificador de trabajos prácticos.
 * Muestra las tareas en una grilla, permite filtrarlas, agregarlas,
 * editarlas, eliminarlas, abrir notas y cerrar la sesión activa.
 */
class MainWidget : public QWidget
{
    Q_OBJECT

private:
    // Lista de tareas cargadas desde el archivo de persistencia.
    QVector<Task> tasks;

    // Controles superiores para filtrar y ejecutar acciones principales.
    QComboBox *cmbEstado;
    QComboBox *cmbPrioridad;
    QPushButton *btnAgregar;
    QPushButton *btnCerrarSesion;

    // Componentes usados para mostrar tareas e historial.
    QWidget *gridContainer;
    QGridLayout *gridLayout;
    QListWidget *historyList;

    // Operaciones internas de carga, guardado y actualización visual.
    void loadTasks();
    void saveTasks();
    void refreshGrid();
    void loadHistory();

    // Calcula el siguiente identificador disponible para una nueva tarea.
    int getNextTaskId() const;

private slots:
    // Slots conectados a botones, filtros y formularios secundarios.
    void applyFilters();
    void openAddTaskForm();
    void addTask(Task task);
    void updateTask(Task task);
    void deleteTask(int id);
    void openEditTaskForm(int id);
    void openNotes(int id);
    void logout();

public:
    // Construye la ventana principal y carga los datos iniciales.
    explicit MainWidget(QWidget *parent = nullptr);

    // Destructor de la ventana principal.
    ~MainWidget();
};

#endif // MAINWIDGET_H
