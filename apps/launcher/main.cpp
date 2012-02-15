#include <QApplication>
#include <QDir>
#include <QFile>
#include <QtDebug>

#include "maindialog.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Now we make sure the current dir is set to application path
    QDir dir(QCoreApplication::applicationDirPath());

    #if defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS") {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }

    QDir pluginsPath(QCoreApplication::applicationDirPath());
    pluginsPath.cdUp();
    pluginsPath.cd("Plugins");

    QStringList libraryPaths;
    libraryPaths << pluginsPath.path() << QCoreApplication::applicationDirPath();
    app.setLibraryPaths(libraryPaths);
    #endif

    QDir::setCurrent(dir.absolutePath());

    // Load the stylesheet
    QFile file("./launcher.qss");

    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    app.setStyleSheet(styleSheet);

    MainDialog dialog;
    return dialog.exec();

}

