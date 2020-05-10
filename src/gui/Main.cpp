#include <QApplication>

//#include "GlossaryApplication.h"
#include "MainViewCreator.h"

int main(int argc, char* argv[])
{
    QApplication app{argc, argv};
    auto mainView = MainViewCreator::createMainView();
    mainView->show();

//    glossary::GlossaryApplication glossaryApplication;
//    glossaryApplication.run();

    return app.exec();
}
