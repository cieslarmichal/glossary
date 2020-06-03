#include "WelcomeTab.h"
#include "ui_WelcomeTab.h"

WelcomeTab::WelcomeTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeTab)
{
    ui->setupUi(this);
}

WelcomeTab::~WelcomeTab()
{
    delete ui;
}
