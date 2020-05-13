#include "GuessTab.h"

#include "ui_GuessTab.h"

namespace glossary::gui::view
{
GuessTab::GuessTab(QWidget* parent) : QWidget(parent), ui(new Ui::GuessTab)
{
    ui->setupUi(this);
}

GuessTab::~GuessTab()
{
    delete ui;
}
}
