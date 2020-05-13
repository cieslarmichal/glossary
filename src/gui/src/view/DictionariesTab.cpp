#include "DictionariesTab.h"

#include "ui_DictionariesTab.h"

namespace glossary::gui::view
{
DictionariesTab::DictionariesTab(QWidget* parent) : QWidget(parent), ui(new Ui::DictionariesTab)
{
    ui->setupUi(this);
}

DictionariesTab::~DictionariesTab()
{
    delete ui;
}
}
