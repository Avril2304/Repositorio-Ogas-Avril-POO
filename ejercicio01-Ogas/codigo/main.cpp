#include <QApplication>
#include <QCoreApplication>

#include "mainwidget.h"
#include "loginwidget.h"
#include "sessionmanager.h"
#include "filemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString basePath = QCoreApplication::applicationDirPath();

    FileManager::initializeFiles(basePath);

    QString sessionPath = basePath + "/session.txt";

    if (SessionManager::hasActiveSession(sessionPath))
    {
        MainWidget w;
        w.show();
        return a.exec();
    }
    else
    {
        LoginWidget login;
        login.show();
        return a.exec();
    }
}