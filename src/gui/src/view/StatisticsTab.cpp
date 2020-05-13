#include "StatisticsTab.h"

#include "ui_StatisticsTab.h"

namespace glossary::gui::view
{
StatisticsTab::StatisticsTab(QWidget* parent) : QWidget(parent), ui(new Ui::StatisticsTab)
{
    ui->setupUi(this);
}

StatisticsTab::~StatisticsTab()
{
    delete ui;
}
}
