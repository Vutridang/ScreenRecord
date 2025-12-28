#include "mainwindow.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget mainWindow;
    mainWindow.setWindowTitle("Screen Recorder");
    mainWindow.resize(300, 100);

    mainWindow.show();

    app.exec();
}
