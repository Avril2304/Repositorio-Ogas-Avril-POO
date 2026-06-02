#include "mainwidget.h"
#include "filemanager.h"
#include "historymanager.h"
#include "taskformwidget.h"
#include "noteswidget.h"
#include "sessionmanager.h"
#include "loginwidget.h"

#include <QCoreApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QScrollArea>
#include <QListWidget>
#include <QMessageBox>

/*
 * Constructor de la ventana principal.
 *
 * Arma la interfaz completa del planificador: filtros, grilla de tareas,
 * botones de acción e historial. Al finalizar, carga los datos persistidos
 * y conecta los eventos de Qt con sus slots correspondientes.
 */
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Planificador de Trabajos Prácticos");
    resize(1000, 650);

    setStyleSheet(
        "QWidget {"
        "   background-color: #1e1e1e;"
        "   color: #f5f5f5;"
        "   font-size: 14px;"
        "}"
        "QLabel {"
        "   color: #f5f5f5;"
        "}"
        "QComboBox {"
        "   background-color: #2d2d30;"
        "   border: 1px solid #3f3f46;"
        "   border-radius: 8px;"
        "   padding: 6px 10px;"
        "   min-width: 120px;"
        "}"
        "QListWidget {"
        "   background-color: #252526;"
        "   border: 1px solid #3f3f46;"
        "   border-radius: 10px;"
        "   padding: 6px;"
        "}"
        "QScrollArea {"
        "   border: 1px solid #3f3f46;"
        "   border-radius: 10px;"
        "   background-color: #252526;"
        "}"
        );

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(12);

    QLabel *titleLabel = new QLabel("Planificador de Trabajos Prácticos");
    titleLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 24px;"
        "   font-weight: bold;"
        "   color: white;"
        "   margin-bottom: 6px;"
        "}"
        );
    mainLayout->addWidget(titleLabel);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setSpacing(10);

    QLabel *lblEstado = new QLabel("Estado:");
    lblEstado->setStyleSheet("font-weight: bold;");

    cmbEstado = new QComboBox();
    cmbEstado->addItem("Todos");
    cmbEstado->addItem("Pendiente");
    cmbEstado->addItem("En progreso");
    cmbEstado->addItem("Entregado");

    QLabel *lblPrioridad = new QLabel("Prioridad:");
    lblPrioridad->setStyleSheet("font-weight: bold;");

    cmbPrioridad = new QComboBox();
    cmbPrioridad->addItem("Todas");
    cmbPrioridad->addItem("Alta");
    cmbPrioridad->addItem("Media");
    cmbPrioridad->addItem("Baja");

    btnAgregar = new QPushButton("Agregar TP");
    btnAgregar->setStyleSheet(
        "QPushButton {"
        "   background-color: #0e639c;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 8px 14px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #1177bb;"
        "}"
        );

    btnCerrarSesion = new QPushButton("Cerrar sesión");
    btnCerrarSesion->setStyleSheet(
        "QPushButton {"
        "   background-color: #7a2e2e;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 8px 14px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #944040;"
        "}"
        );

    topLayout->addWidget(lblEstado);
    topLayout->addWidget(cmbEstado);
    topLayout->addSpacing(10);
    topLayout->addWidget(lblPrioridad);
    topLayout->addWidget(cmbPrioridad);
    topLayout->addStretch();
    topLayout->addWidget(btnAgregar);
    topLayout->addWidget(btnCerrarSesion);

    mainLayout->addLayout(topLayout);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);

    gridContainer = new QWidget();
    gridContainer->setStyleSheet(
        "QWidget {"
        "   background-color: #252526;"
        "   border-radius: 10px;"
        "}"
        );

    gridLayout = new QGridLayout(gridContainer);
    gridLayout->setHorizontalSpacing(20);
    gridLayout->setVerticalSpacing(16);
    gridLayout->setContentsMargins(12, 12, 12, 12);

    scrollArea->setWidget(gridContainer);
    mainLayout->addWidget(scrollArea);

    QLabel *historyTitle = new QLabel("Historial");
    historyTitle->setStyleSheet(
        "QLabel {"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "   margin-top: 6px;"
        "   margin-bottom: 4px;"
        "}"
        );
    mainLayout->addWidget(historyTitle);

    historyList = new QListWidget();
    historyList->setMinimumHeight(140);
    historyList->setMaximumHeight(180);
    mainLayout->addWidget(historyList);

    setLayout(mainLayout);

    loadTasks();
    loadHistory();
    refreshGrid();

    connect(cmbEstado, &QComboBox::currentTextChanged, this, &MainWidget::applyFilters);
    connect(cmbPrioridad, &QComboBox::currentTextChanged, this, &MainWidget::applyFilters);
    connect(btnAgregar, &QPushButton::clicked, this, &MainWidget::openAddTaskForm);
    connect(btnCerrarSesion, &QPushButton::clicked, this, &MainWidget::logout);
}

MainWidget::~MainWidget()
{
}

/*
 * Carga las tareas guardadas en tasks.csv.
 *
 * El archivo se busca en la carpeta del ejecutable para mantener juntos
 * los datos generados por la aplicación.
 */
void MainWidget::loadTasks()
{
    QString basePath = QCoreApplication::applicationDirPath();
    QString tasksPath = basePath + "/tasks.csv";
    tasks = FileManager::loadTasks(tasksPath);
}

/*
 * Guarda el estado actual del vector de tareas.
 *
 * Se llama después de agregar, editar o eliminar una tarea para que
 * los cambios no se pierdan al cerrar la aplicación.
 */
void MainWidget::saveTasks()
{
    QString basePath = QCoreApplication::applicationDirPath();
    QString tasksPath = basePath + "/tasks.csv";
    FileManager::saveTasks(tasksPath, tasks);
}

/*
 * Actualiza la lista visual de historial.
 *
 * Primero limpia el QListWidget y luego agrega cada línea leída
 * desde el archivo history.txt.
 */
void MainWidget::loadHistory()
{
    QString basePath = QCoreApplication::applicationDirPath();
    QString historyPath = basePath + "/history.txt";

    historyList->clear();

    QStringList lines = HistoryManager::loadHistory(historyPath);
    for (int i = 0; i < lines.size(); i++)
    {
        historyList->addItem(lines[i]);
    }
}

/*
 * Calcula un ID nuevo para una tarea.
 *
 * Busca el mayor ID existente y suma uno. Así se evita repetir
 * identificadores aunque se hayan eliminado tareas intermedias.
 */
int MainWidget::getNextTaskId() const
{
    int maxId = 0;

    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].getId() > maxId)
        {
            maxId = tasks[i].getId();
        }
    }

    return maxId + 1;
}

/*
 * Reconstruye la grilla de tareas según los filtros seleccionados.
 *
 * Como los datos pueden cambiar después de agregar, editar, eliminar
 * o filtrar, se eliminan los widgets anteriores y se vuelve a dibujar
 * la tabla completa.
 */
void MainWidget::refreshGrid()
{
    // Limpia todos los widgets cargados previamente en la grilla.
    QLayoutItem *item;
    while ((item = gridLayout->takeAt(0)) != nullptr)
    {
        if (item->widget())
        {
            delete item->widget();
        }
        delete item;
    }

    QString headerStyle =
        "QLabel {"
        "   background-color: #2d2d30;"
        "   color: #ffffff;"
        "   font-weight: bold;"
        "   padding: 8px;"
        "   border-radius: 6px;"
        "}";

    QLabel *lblId = new QLabel("ID");
    QLabel *lblTitulo = new QLabel("Título");
    QLabel *lblMateria = new QLabel("Materia");
    QLabel *lblFecha = new QLabel("Fecha");
    QLabel *lblEstado = new QLabel("Estado");
    QLabel *lblPrioridad = new QLabel("Prioridad");
    QLabel *lblAcciones = new QLabel("Acciones");

    lblId->setStyleSheet(headerStyle);
    lblTitulo->setStyleSheet(headerStyle);
    lblMateria->setStyleSheet(headerStyle);
    lblFecha->setStyleSheet(headerStyle);
    lblEstado->setStyleSheet(headerStyle);
    lblPrioridad->setStyleSheet(headerStyle);
    lblAcciones->setStyleSheet(headerStyle);

    gridLayout->addWidget(lblId, 0, 0);
    gridLayout->addWidget(lblTitulo, 0, 1);
    gridLayout->addWidget(lblMateria, 0, 2);
    gridLayout->addWidget(lblFecha, 0, 3);
    gridLayout->addWidget(lblEstado, 0, 4);
    gridLayout->addWidget(lblPrioridad, 0, 5);
    gridLayout->addWidget(lblAcciones, 0, 6);

    QString filtroEstado = cmbEstado->currentText();
    QString filtroPrioridad = cmbPrioridad->currentText();

    int row = 1;

    // Solo se muestran las tareas que cumplen con ambos filtros activos.
    for (int i = 0; i < tasks.size(); i++)
    {
        bool cumpleEstado = (filtroEstado == "Todos" || tasks[i].getEstado() == filtroEstado);
        bool cumplePrioridad = (filtroPrioridad == "Todas" || tasks[i].getPrioridad() == filtroPrioridad);

        if (cumpleEstado && cumplePrioridad)
        {
            QLabel *idLabel = new QLabel(QString::number(tasks[i].getId()));
            QLabel *tituloLabel = new QLabel(tasks[i].getTitulo());
            QLabel *materiaLabel = new QLabel(tasks[i].getMateria());
            QLabel *fechaLabel = new QLabel(tasks[i].getFechaEntrega());
            QLabel *estadoLabel = new QLabel(tasks[i].getEstado());
            QLabel *prioridadLabel = new QLabel(tasks[i].getPrioridad());

            idLabel->setStyleSheet("padding: 6px;");
            tituloLabel->setStyleSheet("padding: 6px;");
            materiaLabel->setStyleSheet("padding: 6px;");
            fechaLabel->setStyleSheet("padding: 6px;");
            estadoLabel->setStyleSheet("padding: 6px;");
            prioridadLabel->setStyleSheet("padding: 6px;");

            gridLayout->addWidget(idLabel, row, 0);
            gridLayout->addWidget(tituloLabel, row, 1);
            gridLayout->addWidget(materiaLabel, row, 2);
            gridLayout->addWidget(fechaLabel, row, 3);
            gridLayout->addWidget(estadoLabel, row, 4);
            gridLayout->addWidget(prioridadLabel, row, 5);

            QWidget *accionesWidget = new QWidget();
            QHBoxLayout *accionesLayout = new QHBoxLayout(accionesWidget);
            accionesLayout->setContentsMargins(0, 0, 0, 0);
            accionesLayout->setSpacing(8);

            QPushButton *btnEditar = new QPushButton("Editar");
            QPushButton *btnEliminar = new QPushButton("Eliminar");
            QPushButton *btnNotas = new QPushButton("Notas");

            btnEditar->setStyleSheet(
                "QPushButton {"
                "   background-color: #3a6ea5;"
                "   color: white;"
                "   border: none;"
                "   border-radius: 6px;"
                "   padding: 6px 10px;"
                "}"
                "QPushButton:hover {"
                "   background-color: #4b82c1;"
                "}"
                );

            btnEliminar->setStyleSheet(
                "QPushButton {"
                "   background-color: #a53a3a;"
                "   color: white;"
                "   border: none;"
                "   border-radius: 6px;"
                "   padding: 6px 10px;"
                "}"
                "QPushButton:hover {"
                "   background-color: #bf4a4a;"
                "}"
                );

            btnNotas->setStyleSheet(
                "QPushButton {"
                "   background-color: #5c4b8a;"
                "   color: white;"
                "   border: none;"
                "   border-radius: 6px;"
                "   padding: 6px 10px;"
                "}"
                "QPushButton:hover {"
                "   background-color: #715fb0;"
                "}"
                );

            accionesLayout->addWidget(btnEditar);
            accionesLayout->addWidget(btnEliminar);
            accionesLayout->addWidget(btnNotas);

            // Cada botón captura el ID de la tarea para ejecutar la acción correcta.
            connect(btnEliminar, &QPushButton::clicked, this, [=]() {
                deleteTask(tasks[i].getId());
            });

            connect(btnEditar, &QPushButton::clicked, this, [=]() {
                openEditTaskForm(tasks[i].getId());
            });

            connect(btnNotas, &QPushButton::clicked, this, [=]() {
                openNotes(tasks[i].getId());
            });

            gridLayout->addWidget(accionesWidget, row, 6);

            row++;
        }
    }
}

/*
 * Aplica los filtros de estado y prioridad.
 *
 * Los filtros no modifican el vector de tareas: solamente vuelven a
 * dibujar la grilla con los elementos que corresponden.
 */
void MainWidget::applyFilters()
{
    refreshGrid();
}

/*
 * Abre el formulario para cargar un nuevo trabajo práctico.
 *
 * Cuando el formulario emite taskSaved, la tarea nueva se recibe en addTask.
 */
void MainWidget::openAddTaskForm()
{
    TaskFormWidget *form = new TaskFormWidget();
    form->show();

    connect(form, &TaskFormWidget::taskSaved, this, &MainWidget::addTask);
}

/*
 * Agrega una tarea nueva al sistema.
 *
 * El formulario crea la tarea con ID 0; acá se asigna el ID definitivo,
 * se guarda en archivo, se registra el historial y se refresca la vista.
 */
void MainWidget::addTask(Task task)
{
    task.setId(getNextTaskId());
    tasks.append(task);
    saveTasks();

    QString basePath = QCoreApplication::applicationDirPath();
    QString historyPath = basePath + "/history.txt";
    HistoryManager::saveAction(historyPath, "Se agregó el TP: " + task.getTitulo());

    loadHistory();
    refreshGrid();
}

/*
 * Reemplaza una tarea existente por los datos editados.
 *
 * Se busca por ID para mantener la posición lógica de la tarea y evitar
 * modificar otra entrada por accidente.
 */
void MainWidget::updateTask(Task task)
{
    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].getId() == task.getId())
        {
            tasks[i] = task;
            saveTasks();

            QString basePath = QCoreApplication::applicationDirPath();
            QString historyPath = basePath + "/history.txt";
            HistoryManager::saveAction(historyPath, "Se editó el TP: " + task.getTitulo());

            loadHistory();
            refreshGrid();
            return;
        }
    }
}

/*
 * Elimina una tarea después de pedir confirmación.
 *
 * Si el usuario acepta, se quita del vector, se persiste el cambio
 * y se registra la acción en el historial.
 */
void MainWidget::deleteTask(int id)
{
    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].getId() == id)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirmar eliminación",
                                          "¿Seguro que desea eliminar este trabajo práctico?",
                                          QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::No)
            {
                return;
            }

            QString titulo = tasks[i].getTitulo();
            tasks.remove(i);
            saveTasks();

            QString basePath = QCoreApplication::applicationDirPath();
            QString historyPath = basePath + "/history.txt";
            HistoryManager::saveAction(historyPath, "Se eliminó el TP: " + titulo);

            loadHistory();
            refreshGrid();
            return;
        }
    }
}

/*
 * Abre el formulario en modo edición para la tarea indicada.
 *
 * El constructor recibe la tarea actual para precargar sus campos.
 */
void MainWidget::openEditTaskForm(int id)
{
    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].getId() == id)
        {
            TaskFormWidget *form = new TaskFormWidget(tasks[i]);
            form->show();

            connect(form, &TaskFormWidget::taskSaved, this, &MainWidget::updateTask);
            return;
        }
    }
}

/*
 * Abre la ventana de notas de una tarea.
 *
 * Las notas se guardan en un archivo independiente cuyo nombre incluye
 * el ID de la tarea.
 */
void MainWidget::openNotes(int id)
{
    NotesWidget *notes = new NotesWidget(id);
    notes->show();

    QString basePath = QCoreApplication::applicationDirPath();
    QString historyPath = basePath + "/history.txt";
    HistoryManager::saveAction(historyPath, "Se abrieron notas del TP ID " + QString::number(id));
    loadHistory();
}

/*
 * Cierra la sesión actual.
 *
 * Limpia el archivo de sesión, registra la salida y vuelve a mostrar
 * la ventana de login.
 */
void MainWidget::logout()
{
    QString basePath = QCoreApplication::applicationDirPath();
    QString sessionPath = basePath + "/session.txt";
    QString historyPath = basePath + "/history.txt";

    SessionManager::clearSession(sessionPath);
    HistoryManager::saveAction(historyPath, "Se cerró la sesión");

    LoginWidget *login = new LoginWidget();
    login->show();

    close();
}
