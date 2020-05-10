#include "TranslatorTab.h"
#include "ui_TranslatorTab.h"

TranslatorTab::TranslatorTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TranslatorTab)
{
    ui->setupUi(this);
}

TranslatorTab::~TranslatorTab()
{
    delete ui;
}
