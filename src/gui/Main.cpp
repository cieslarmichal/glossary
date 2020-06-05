#include <QApplication>

#include "Gui.h"

int main(int argc, char* argv[])
{
    QApplication app{argc, argv};

    glossary::gui::Gui gui{app};
    gui.show();

    return app.exec();
}
