#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget mainWindow;
    mainWindow.setWindowTitle("Screen Recorder");
    mainWindow.resize(300, 100);

    QVBoxLayout *layout = new QVBoxLayout(&mainWindow);

    QLabel *titleLabel = new QLabel("Screen Recorder");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 22px; color: blue;");

    layout->addWidget(titleLabel);

    QPushButton *recordButton = new QPushButton("Record");
    recordButton->setStyleSheet("font-size: 16px; color: white; background-color: green");
    layout->addWidget(recordButton);

    mainWindow.show();

    app.exec();
}
