#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QProcess>
#include <QFileDialog>
#include <QDebug>


const QString ffmpeg = "D:/project_bai_tap/c_project/QT/ScreenRecordApp/ScreenRecordApp/ffmpeg_build/bin/ffmpeg.exe";
void startRecording(QProcess &recordProcess, QPushButton *recordButton, QString &outputFilePath, QWidget *mainWindow){
    recordButton->setText("Stop Recoding");
    recordButton->setStyleSheet("font-size:16px; color: white; background-color: red");

    QString command = ffmpeg;

    QStringList arguments;

//    arguments << "-y" //Overwriting output file without asking
//              << "-f" << "gdigrab"  // use GDI GRAB to capture screen
//              << "-i" << "desktop" // Capture the entire screen
//              << "-f" << "dshow" // use directs show for audio capture
//              << "-i" << "audio=Microphone Array (Intel(R) Smart Sound Technology for Digital Microphones)" // audio device
//              << "-c:v" << "libx264" // Encode video with x264
//              << "-preset" << "ultrafast" // Encoding preset
//              << "-c:a" << "aac" // Encoding audio with ACC
//              << "-pix_fmt" << "yuv420p" // pixel format for compatability
//              << outputFilePath; // output file

    arguments << "-y"
              << "-f" << "gdigrab"
              << "-i" << "desktop"
              << "-f" << "dshow"
              << "-i" << "audio=Microphone (USB Advanced Audio Device)"
              << "-c:v" << "libx264"
              << "-preset" << "ultrafast"
              << "-c:a" << "aac"
              << "-pix_fmt" << "yuv420p"
              << outputFilePath;

    recordProcess.start(command,arguments);

    if(!recordProcess.waitForStarted()){
        qDebug() << "Failed to start recoding";
        recordButton->setText("Record");
        recordButton->setStyleSheet("font-size:16px; background-color: green");
    }else{
        qDebug() << "Recording Started...";
        mainWindow->showMinimized();
    }

}

void stopRecording(QProcess &recordProcess, QPushButton *recordButton, QString &outputFilePath, QWidget *mainWindow){
    if (recordProcess.state() == QProcess::Running) {
        recordProcess.write("q\n");
        recordProcess.waitForFinished();

         qDebug() << "Recording Stopped. Saved to " << outputFilePath;
    }

    recordButton->setText("Record");
    recordButton->setStyleSheet("font-size: 16px; color:white; background-color: green;");
    mainWindow->showNormal();
}

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

    QProcess recordProcess;
    QString outputFilePath;

    QObject::connect(recordButton, &QPushButton::clicked, [&](){
        if(recordButton->text() == "Record"){
            outputFilePath = QFileDialog::getSaveFileName(&mainWindow, "Save Recording", "", "Video Files (*.mp4)");

            if(!outputFilePath.isEmpty()){
                startRecording(recordProcess, recordButton, outputFilePath, &mainWindow);
            }
        }else{
            stopRecording(recordProcess, recordButton, outputFilePath, &mainWindow);
        }
    });

    mainWindow.show();

    return app.exec();
}
