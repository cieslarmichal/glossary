#include <QApplication>

//#include "GlossaryApplication.h"
#include "Gui.h"

int main(int argc, char* argv[])
{
    QApplication app{argc, argv};
    Gui gui;
    gui.show();

//    glossary::GlossaryApplication glossaryApplication;
//    glossaryApplication.run();

    return app.exec();
}
