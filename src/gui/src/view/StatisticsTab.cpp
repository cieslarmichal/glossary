#include "StatisticsTab.h"

#include <QPen>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>

#include "ui_StatisticsTab.h"

namespace glossary::gui::view
{
StatisticsTab::StatisticsTab(QWidget* parent)
    : QChartView(parent),
      currentDictionaryName{boost::none},
      ui(new Ui::StatisticsTab),
      chartView{std::make_unique<QChartView>(this)},
      chart{std::make_unique<QChart>()},
      pieSeries{nullptr}
{
    ui->setupUi(this);
    ui->listOfDictionaries->setModel(&dictionaryNames);
    setChart(chart.get());
    chartView->setChart(chart.get());
    ui->layoutChartView->addWidget(chartView.get());
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->show();
}

StatisticsTab::~StatisticsTab()
{
    if (pieSeries)
    {
        chart->removeSeries(pieSeries.get());
    }
    delete ui;
}

void StatisticsTab::setDictionariesStatistics(const DictionariesStatistics& dictionariesStatisticsInit)
{
    dictionariesStatistics = dictionariesStatisticsInit;

    QStringList dictionaryNamesFromStatistics;
    for (const auto& dictionaryStatistics : dictionariesStatistics)
    {
        dictionaryNamesFromStatistics.push_back(QString::fromStdString(dictionaryStatistics.dictionaryName));
    }
    dictionaryNames.setStringList(dictionaryNamesFromStatistics);
}

void StatisticsTab::onDictionaryStatisticsReceived(const DictionaryStatistics& updatedDictionaryStatistics)
{
    for (auto& dictionaryStatistics : dictionariesStatistics)
    {
        if (dictionaryStatistics.dictionaryName == updatedDictionaryStatistics.dictionaryName)
        {
            dictionaryStatistics = updatedDictionaryStatistics;
        }
    }

    if (currentDictionaryName &&
        currentDictionaryName->toStdString() == updatedDictionaryStatistics.dictionaryName)
    {
        updateCurrentDictionaryStatistics(updatedDictionaryStatistics);
    }
}

void StatisticsTab::onDictionariesStatisticsReceived(const DictionariesStatistics& dictionaryStatistics)
{
    setDictionariesStatistics(dictionaryStatistics);
}

void StatisticsTab::on_listOfDictionaries_clicked(const QModelIndex& dictionaryNameIndex)
{
    QString dictionaryName = dictionaryNameIndex.data(Qt::DisplayRole).toString();
    currentDictionaryName = dictionaryName;

    auto dictionaryStatistics = getDictionaryStatistics(dictionaryName);

    updateCurrentDictionaryStatistics(dictionaryStatistics);
}

void StatisticsTab::updateCurrentDictionaryStatistics(const DictionaryStatistics& dictionaryStatistics)
{
    ui->editCorrectAnswers->setText(
        QString::fromStdString(std::to_string(dictionaryStatistics.correctAnswers)));
    ui->editIncorrectAnswers->setText(
        QString::fromStdString(std::to_string(dictionaryStatistics.incorrectAnswers)));
    double efficiency = static_cast<double>(dictionaryStatistics.correctAnswers) /
                        (dictionaryStatistics.correctAnswers + dictionaryStatistics.incorrectAnswers);
    int efficiencyPercents = static_cast<int>(efficiency * 100);
    ui->editEfficiency->setText(QString::fromStdString(std::to_string(efficiencyPercents) + "%"));
    updateChartView(dictionaryStatistics);
}

void StatisticsTab::updateChartView(const DictionaryStatistics& dictionaryStatistics)
{
    if (pieSeries)
    {
        chart->removeSeries(pieSeries.get());
    }

    pieSeries = std::make_unique<QPieSeries>();

    double amountOfALlAnswers =
        static_cast<double>(dictionaryStatistics.correctAnswers + dictionaryStatistics.incorrectAnswers);
    double percentOfCorrectAnswers =
        static_cast<double>(dictionaryStatistics.correctAnswers) / amountOfALlAnswers;
    double percentOfIncorrectAnswers =
        static_cast<double>(dictionaryStatistics.incorrectAnswers) / amountOfALlAnswers;
    pieSeries->append("Correct answers", percentOfCorrectAnswers);
    pieSeries->append("Incorrect answers", percentOfIncorrectAnswers);

    QPieSlice* correctAnswersSlice = pieSeries->slices().at(0);
    correctAnswersSlice->setLabel("Correct answers");
    correctAnswersSlice->setPen(QPen(Qt::darkGreen, 2));
    correctAnswersSlice->setBrush(Qt::green);

    QPieSlice* incorrectAnswersSlice = pieSeries->slices().at(1);
    incorrectAnswersSlice->setLabel("Incorrect answers");
    incorrectAnswersSlice->setPen(QPen(Qt::darkRed, 2));
    incorrectAnswersSlice->setBrush(Qt::red);

    pieSeries->setLabelsPosition(QPieSlice::LabelOutside);

    chart->addSeries(pieSeries.get());
    chart->setTitle("Dictionary statistics - answers from guessing english words");
    chartView->show();
}

DictionaryStatistics StatisticsTab::getDictionaryStatistics(const QString& dictionaryName) const
{
    auto foundDictionarStatistics = std::find_if(
        dictionariesStatistics.begin(), dictionariesStatistics.end(), [&](const DictionaryStatistics& stats) {
            return stats.dictionaryName == dictionaryName.toStdString();
        });
    if (foundDictionarStatistics != dictionariesStatistics.end())
    {
        return *foundDictionarStatistics;
    }
    return {};
}

void StatisticsTab::on_buttonResetDictionaries_clicked()
{
    emit notifyAboutResetStatistics();
}

}


