#include "StatisticsTab.h"

#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>

#include "ui_StatisticsTab.h"

namespace glossary::gui::view
{
StatisticsTab::StatisticsTab(QWidget* parent) : QWidget(parent), ui(new Ui::StatisticsTab)
{
    ui->setupUi(this);
    chartView = new QChartView{this};

    QBarSet* set0 = new QBarSet("bar1");

    *set0 << 1 << 4 << 3 << 7 << 2 << 5 << 1 << 3 << 3 << 2 << 1 << 6 << 7 << 5;

    QBarSeries* series = new QBarSeries;
    series->append(set0);

    QChart* chart = new QChart;
    chartView->setChart(chart);
    chart->addSeries(series);

    // filter items
    QList<QGraphicsRectItem*> rect_items;
    for (QGraphicsItem* it : chartView->items())
    {
        if (QGraphicsRectItem* rect = qgraphicsitem_cast<QGraphicsRectItem*>(it))
        {
            if (rect->parentItem() != chart && rect->parentItem()->parentItem() == chart)
            {
                rect_items << rect;
            }
        }
    }
    chartView->show();
}

StatisticsTab::~StatisticsTab()
{
    delete ui;
}

void StatisticsTab::onDictionaryStatisticsReceived(const DictionaryStatistics&) {}

void StatisticsTab::onDictionariesStatisticsReceived(const DictionariesStatistics&) {}
}
