#ifndef NOTESWIDGET_H
#define NOTESWIDGET_H

#include <QWidget>

class QTextEdit;
class QPushButton;

/*
 * Clase: NotesWidget
 * ----------------------------
 * Ventana para escribir y guardar notas asociadas a una tarea.
 * Cada tarea utiliza su propio archivo de notas identificado por su ID.
 */
class NotesWidget : public QWidget
{
    Q_OBJECT

private:
    // Identificador de la tarea cuyas notas se están editando.
    int taskId;

    // Editor de texto y botón de guardado.
    QTextEdit *txtNotes;
    QPushButton *btnGuardar;

    // Carga el contenido del archivo de notas de la tarea actual.
    void loadNotes();

private slots:
    // Guarda el texto escrito en el archivo correspondiente.
    void saveNotes();

public:
    // Construye la ventana de notas para la tarea indicada.
    explicit NotesWidget(int taskId, QWidget *parent = nullptr);
};

#endif // NOTESWIDGET_H
