#include "StatisticsTab.h"

#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include "ui_StatisticsTab.h"
#include <QtCharts/QPieSeries>
#include <QPen>

namespace glossary::gui::view
{
StatisticsTab::StatisticsTab(QWidget* parent) : QChartView(parent), ui(new Ui::StatisticsTab)
{
    ui->setupUi(this);
    chartView= new QChartView{this};

    QChart* chart = new QChart();
    setChart(chart);
    chartView->setChart(chart);

    ui->layoutChartView->addWidget(chartView,0,0);

    QPieSeries * series = new QPieSeries();

    series->append("Correct answers", .60);
    series->append("Incorrect answers", .40);

    QPieSlice * slice = series->slices().at(0);
//    slice->setLabelVisible();
    slice->setLabel("Correct answers");
    slice->setPen(QPen(Qt::darkGreen, 2));
    slice->setBrush(Qt::green);

    QPieSlice *slice1 = series->slices().at(1);
//    slice1->setLabelVisible();
    slice1->setLabel("Incorrect answers");
//    slice1->setLabel(QString("%1%").arg(100*slice1->percentage(), 0, 'f', 1));
    slice1->setPen(QPen(Qt::darkRed, 2));
    slice1->setBrush(Qt::red);

//    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelOutside);

    chart->addSeries(series);
    chart->setTitle("Dictionary statistics");
//    chart->legend()->hide();

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->show();
}

StatisticsTab::~StatisticsTab()
{
    delete ui;
}

void StatisticsTab::onDictionaryStatisticsReceived(const DictionaryStatistics&) {}

void StatisticsTab::onDictionariesStatisticsReceived(const DictionariesStatistics&) {}
}
