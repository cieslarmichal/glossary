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
    ui->listOfDictionaries->setModel(&dictionaryNames);
    chartView= new QChartView{this};
    chartView->setRenderHint(QPainter::Antialiasing);
}

StatisticsTab::~StatisticsTab()
{
    delete chartView;
    delete ui;
}

void StatisticsTab::setDictionariesStatistics(const DictionariesStatistics & dictionariesStatisticsInit)
{
    dictionariesStatistics = dictionariesStatisticsInit;

    QStringList dictionaryNamesFromStatistics;
    for(const auto& dictionaryStatistics : dictionariesStatistics)
    {
        dictionaryNamesFromStatistics.push_back(QString::fromStdString(dictionaryStatistics.dictionaryName));
    }
    dictionaryNames.setStringList(dictionaryNamesFromStatistics);
}

void StatisticsTab::onDictionaryStatisticsReceived(const DictionaryStatistics&)
{

}

void StatisticsTab::onDictionariesStatisticsReceived(const DictionariesStatistics& dictionaryStatistics)
{
    setDictionariesStatistics(dictionaryStatistics);
}

void StatisticsTab::on_listOfDictionaries_clicked(const QModelIndex &dictionaryNameIndex)
{
    QString dictionaryName = dictionaryNameIndex.data(Qt::DisplayRole).toString();

    auto dictionaryStatistics = getDictionaryStatistics(dictionaryName);

    updateCurrentDictionaryStatistics(dictionaryStatistics);
}

void StatisticsTab::updateCurrentDictionaryStatistics(const DictionaryStatistics & dictionaryStatistics)
{
    ui->editCorrectAnswers->setText(QString::fromStdString(std::to_string(dictionaryStatistics.correctAnswers)));
    ui->editIncorrectAnswers->setText(QString::fromStdString(std::to_string(dictionaryStatistics.incorrectAnswers)));
    double efficiency = dictionaryStatistics.correctAnswers / dictionaryStatistics.incorrectAnswers;
    ui->editEfficiency->setText(QString::fromStdString(std::to_string(efficiency)));
    updateChartView(dictionaryStatistics);
}

void StatisticsTab::updateChartView(const DictionaryStatistics &)
{
    QChart* chart = new QChart();
    setChart(chart);
    chartView->setChart(chart);
    ui->layoutChartView->addWidget(chartView,0,0);

    QPieSeries * series = new QPieSeries();

    series->append("Correct answers", .60);
    series->append("Incorrect answers", .40);

    QPieSlice * slice = series->slices().at(0);
    slice->setLabel("Correct answers");
    slice->setPen(QPen(Qt::darkGreen, 2));
    slice->setBrush(Qt::green);

    QPieSlice *slice1 = series->slices().at(1);
    slice1->setLabel("Incorrect answers");
    slice1->setPen(QPen(Qt::darkRed, 2));
    slice1->setBrush(Qt::red);

    series->setLabelsPosition(QPieSlice::LabelOutside);

    chart->addSeries(series);
    chart->setTitle("Dictionary statistics");

    chartView->show();
}

DictionaryStatistics StatisticsTab::getDictionaryStatistics(const QString &dictionaryName) const
{
    auto foundDictionarStatistics =
        std::find_if(dictionariesStatistics.begin(), dictionariesStatistics.end(),
                     [&](const DictionaryStatistics& stats) { return stats.dictionaryName == dictionaryName.toStdString(); });
    if (foundDictionarStatistics != dictionariesStatistics.end())
    {
        return *foundDictionarStatistics;
    }
    return {};
}

}
