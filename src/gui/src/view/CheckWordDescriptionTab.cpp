#include "CheckWordDescriptionTab.h"

#include "ui_CheckWordDescriptionTab.h"

namespace glossary::gui::view
{
CheckWordDescriptionTab::CheckWordDescriptionTab(QWidget* parent)
    : QWidget(parent), ui(new Ui::CheckWordDescriptionTab)
{
    ui->setupUi(this);
}

CheckWordDescriptionTab::~CheckWordDescriptionTab()
{
    delete ui;
}
}
