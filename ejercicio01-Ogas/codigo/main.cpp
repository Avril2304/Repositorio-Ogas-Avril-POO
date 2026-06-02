#include <QApplication>
#include <QCoreApplication>

#include "mainwidget.h"
#include "loginwidget.h"
#include "sessionmanager.h"
#include "filemanager.h"

int main(int argc, char *argv[])
{
    // QApplication inicializa el entorno gráfico de Qt.
    QApplication a(argc, argv);

    // Se usa la carpeta del ejecutable para guardar archivos de datos locales.
    QString basePath = QCoreApplication::applicationDirPath();

    // Asegura que existan users.csv, tasks.csv, session.txt e history.txt.
    FileManager::initializeFiles(basePath);

    QString sessionPath = basePath + "/session.txt";

    // Si hay una sesión vigente, se entra directo al planificador.
    if (SessionManager::hasActiveSession(sessionPath))
    {
        MainWidget w;
        w.show();
        return a.exec();
    }
    else
    {
        // Si no hay sesión activa, se solicita el inicio de sesión.
        LoginWidget login;
        login.show();
        return a.exec();
    }
}
