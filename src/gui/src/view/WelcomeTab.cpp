#include "WelcomeTab.h"

#include <QDir>
#include <QFileDialog>

#include "fileSystem/GetProjectPath.h"
#include "ui_WelcomeTab.h"

namespace
{
const auto resourceDirectoryPath = common::fileSystem::getProjectPath("glossary") + "src/gui/resources/";
}

namespace glossary::gui::view
{
WelcomeTab::WelcomeTab(QWidget* parent) : QWidget(parent), ui(new Ui::WelcomeTab)
{
    ui->setupUi(this);
}

WelcomeTab::~WelcomeTab()
{
    delete ui;
}

}
