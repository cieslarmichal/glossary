#include "GuessTab.h"
#include "ui_GuessTab.h"

GuessTab::GuessTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuessTab)
{
    ui->setupUi(this);
}

GuessTab::~GuessTab()
{
    delete ui;
}
