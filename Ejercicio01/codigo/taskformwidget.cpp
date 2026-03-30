#include "taskformwidget.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

TaskFormWidget::TaskFormWidget(QWidget *parent)
    : QWidget(parent), editMode(false)
{
    setWindowTitle("Agregar Trabajo Práctico");
    resize(430, 360);

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
        "QLineEdit, QComboBox {"
        "   background-color: #2d2d30;"
        "   border: 1px solid #3f3f46;"
        "   border-radius: 8px;"
        "   padding: 8px;"
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

    QLabel *titleLabel = new QLabel("Nuevo trabajo práctico");
    titleLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 22px;"
        "   font-weight: bold;"
        "   margin-bottom: 10px;"
        "}"
        );

    txtTitulo = new QLineEdit(this);
    txtMateria = new QLineEdit(this);
    txtFecha = new QLineEdit(this);

    cmbEstado = new QComboBox(this);
    cmbEstado->addItem("Pendiente");
    cmbEstado->addItem("En progreso");
    cmbEstado->addItem("Entregado");

    cmbPrioridad = new QComboBox(this);
    cmbPrioridad->addItem("Alta");
    cmbPrioridad->addItem("Media");
    cmbPrioridad->addItem("Baja");

    btnGuardar = new QPushButton("Guardar", this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(10);

    layout->addWidget(titleLabel);
    layout->addWidget(new QLabel("Título:"));
    layout->addWidget(txtTitulo);
    layout->addWidget(new QLabel("Materia:"));
    layout->addWidget(txtMateria);
    layout->addWidget(new QLabel("Fecha de entrega:"));
    layout->addWidget(txtFecha);
    layout->addWidget(new QLabel("Estado:"));
    layout->addWidget(cmbEstado);
    layout->addWidget(new QLabel("Prioridad:"));
    layout->addWidget(cmbPrioridad);
    layout->addWidget(btnGuardar);

    setLayout(layout);

    connect(btnGuardar, &QPushButton::clicked, this, &TaskFormWidget::handleSave);
}

TaskFormWidget::TaskFormWidget(Task task, QWidget *parent)
    : QWidget(parent), currentTask(task), editMode(true)
{
    setWindowTitle("Editar Trabajo Práctico");
    resize(430, 360);

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
        "QLineEdit, QComboBox {"
        "   background-color: #2d2d30;"
        "   border: 1px solid #3f3f46;"
        "   border-radius: 8px;"
        "   padding: 8px;"
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

    QLabel *titleLabel = new QLabel("Editar trabajo práctico");
    titleLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 22px;"
        "   font-weight: bold;"
        "   margin-bottom: 10px;"
        "}"
        );

    txtTitulo = new QLineEdit(this);
    txtMateria = new QLineEdit(this);
    txtFecha = new QLineEdit(this);

    cmbEstado = new QComboBox(this);
    cmbEstado->addItem("Pendiente");
    cmbEstado->addItem("En progreso");
    cmbEstado->addItem("Entregado");

    cmbPrioridad = new QComboBox(this);
    cmbPrioridad->addItem("Alta");
    cmbPrioridad->addItem("Media");
    cmbPrioridad->addItem("Baja");

    btnGuardar = new QPushButton("Guardar cambios", this);

    txtTitulo->setText(task.getTitulo());
    txtMateria->setText(task.getMateria());
    txtFecha->setText(task.getFechaEntrega());
    cmbEstado->setCurrentText(task.getEstado());
    cmbPrioridad->setCurrentText(task.getPrioridad());

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(10);

    layout->addWidget(titleLabel);
    layout->addWidget(new QLabel("Título:"));
    layout->addWidget(txtTitulo);
    layout->addWidget(new QLabel("Materia:"));
    layout->addWidget(txtMateria);
    layout->addWidget(new QLabel("Fecha de entrega:"));
    layout->addWidget(txtFecha);
    layout->addWidget(new QLabel("Estado:"));
    layout->addWidget(cmbEstado);
    layout->addWidget(new QLabel("Prioridad:"));
    layout->addWidget(cmbPrioridad);
    layout->addWidget(btnGuardar);

    setLayout(layout);

    connect(btnGuardar, &QPushButton::clicked, this, &TaskFormWidget::handleSave);
}

void TaskFormWidget::handleSave()
{
    QString titulo = txtTitulo->text().trimmed();
    QString materia = txtMateria->text().trimmed();
    QString fecha = txtFecha->text().trimmed();
    QString estado = cmbEstado->currentText();
    QString prioridad = cmbPrioridad->currentText();

    if (titulo.isEmpty() || materia.isEmpty() || fecha.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Complete todos los campos.");
        return;
    }

    Task task;

    if (editMode)
    {
        task.setId(currentTask.getId());
    }
    else
    {
        task.setId(0);
    }

    task.setTitulo(titulo);
    task.setMateria(materia);
    task.setFechaEntrega(fecha);
    task.setEstado(estado);
    task.setPrioridad(prioridad);

    emit taskSaved(task);
    close();
}