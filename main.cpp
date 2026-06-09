
#include <QFile>

#include "ui/MainWindow.h"

int main(int argc,char* argv[]) {
    QApplication app(argc, argv);
    QFile styleFile(":/style.qss");
    styleFile.open(QFile::ReadOnly);
    app.setStyleSheet(styleFile.readAll());
    MainWindow window;
    window.show();
    app.exec();
}


