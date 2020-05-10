#include "DictionariesTab.h"
#include "ui_DictionariesTab.h"

DictionariesTab::DictionariesTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DictionariesTab)
{
    ui->setupUi(this);
}

DictionariesTab::~DictionariesTab()
{
    delete ui;
}
