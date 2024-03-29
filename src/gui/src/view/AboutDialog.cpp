#include "AboutDialog.h"

#include "fileSystem/GetProjectPath.h"
#include "ui_AboutDialog.h"

namespace glossary::gui::view
{
namespace
{
const auto resourceDirectoryPath = common::fileSystem::getProjectPath("glossary") + "src/gui/resources/";
const auto glossaryIconPath = resourceDirectoryPath + "glossaryIcon.png";
}

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent), ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    auto glossaryIcon = QPixmap(glossaryIconPath.c_str());

    int width = ui->labelGlossaryIcon->width();

    int height = ui->labelGlossaryIcon->height();

    ui->labelGlossaryIcon->setPixmap(glossaryIcon.scaled(width, height, Qt::KeepAspectRatio));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
}
