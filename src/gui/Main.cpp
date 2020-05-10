#include <QApplication>

//#include "GlossaryApplication.h"
#include "src/MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app{argc, argv};
    MainWindow mainWindow;
    mainWindow.show();

//    glossary::GlossaryApplication glossaryApplication;
//    glossaryApplication.run();

    return QApplication::exec();
}
