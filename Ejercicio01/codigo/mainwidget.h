#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QVector>
#include "task.h"

class QGridLayout;
class QComboBox;
class QListWidget;
class QPushButton;

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    QVector<Task> tasks;

    QComboBox *cmbEstado;
    QComboBox *cmbPrioridad;
    QPushButton *btnAgregar;
    QPushButton *btnCerrarSesion;

    QWidget *gridContainer;
    QGridLayout *gridLayout;
    QListWidget *historyList;

    void loadTasks();
    void saveTasks();
    void refreshGrid();
    void loadHistory();
    int getNextTaskId() const;

private slots:
    void applyFilters();
    void openAddTaskForm();
    void addTask(Task task);
    void updateTask(Task task);
    void deleteTask(int id);
    void openEditTaskForm(int id);
    void openNotes(int id);
    void logout();

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
};

#endif // MAINWIDGET_H