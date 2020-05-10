#include "StatisticsTab.h"
#include "ui_StatisticsTab.h"

StatisticsTab::StatisticsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsTab)
{
    ui->setupUi(this);
}

StatisticsTab::~StatisticsTab()
{
    delete ui;
}
