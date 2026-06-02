#include "noteswidget.h"

#include <QCoreApplication>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

/*
 * Constructor de la ventana de notas.
 *
 * Recibe el ID de la tarea para saber qué archivo de notas debe leer
 * y guardar. Luego arma la interfaz y carga el contenido existente.
 */
NotesWidget::NotesWidget(int taskId, QWidget *parent)
    : QWidget(parent), taskId(taskId)
{
    setWindowTitle("Notas del Trabajo Práctico");
    resize(560, 430);

    setStyleSheet(
        "QWidget {"
        "   background-color: #1e1e1e;"
        "   color: #f5f5f5;"
        "   font-size: 14px;"
        "}"
        "QLabel {"
        "   color: #f5f5f5;"
        "   font-weight: bold;"
        "}"
        "QTextEdit {"
        "   background-color: #252526;"
        "   border: 1px solid #3f3f46;"
        "   border-radius: 10px;"
        "   padding: 10px;"
        "   color: white;"
        "}"
        "QPushButton {"
        "   background-color: #0e639c;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 8px 12px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #1177bb;"
        "}"
        );

    QLabel *titleLabel = new QLabel("Notas del trabajo práctico");
    titleLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 22px;"
        "   font-weight: bold;"
        "   margin-bottom: 8px;"
        "}"
        );

    QLabel *subtitleLabel = new QLabel("Escriba las notas y guárdelas manualmente.");
    subtitleLabel->setStyleSheet(
        "QLabel {"
        "   color: #cfcfcf;"
        "   font-weight: normal;"
        "   margin-bottom: 8px;"
        "}"
        );

    txtNotes = new QTextEdit(this);
    btnGuardar = new QPushButton("Guardar notas", this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(12);

    layout->addWidget(titleLabel);
    layout->addWidget(subtitleLabel);
    layout->addWidget(txtNotes);
    layout->addWidget(btnGuardar);

    setLayout(layout);

    loadNotes();

    connect(btnGuardar, &QPushButton::clicked, this, &NotesWidget::saveNotes);
}

/*
 * Carga las notas guardadas para la tarea actual.
 *
 * Si el archivo todavía no existe, simplemente deja el editor vacío
 * para que el usuario pueda crear las notas por primera vez.
 */
void NotesWidget::loadNotes()
{
    QString basePath = QCoreApplication::applicationDirPath();
    QString notesPath = basePath + "/notes_" + QString::number(taskId) + ".txt";

    QFile file(notesPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream in(&file);
    txtNotes->setPlainText(in.readAll());
    file.close();
}

/*
 * Guarda el contenido del editor de texto.
 *
 * El archivo se sobrescribe completo para que quede exactamente igual
 * a lo que el usuario ve en pantalla.
 */
void NotesWidget::saveNotes()
{
    QString basePath = QCoreApplication::applicationDirPath();
    QString notesPath = basePath + "/notes_" + QString::number(taskId) + ".txt";

    QFile file(notesPath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "No se pudieron guardar las notas.");
        return;
    }

    QTextStream out(&file);
    out << txtNotes->toPlainText();
    file.close();

    QMessageBox::information(this, "Éxito", "Notas guardadas manualmente.");
}
