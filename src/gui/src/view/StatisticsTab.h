#pragma once

#include <QChartView>
#include <QStringListModel>
#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <memory>

#include "DictionaryStatistics.h"
QT_CHARTS_USE_NAMESPACE

namespace glossary::gui::view
{
namespace Ui
{
class StatisticsTab;
}

class StatisticsTab : public QChartView
{
    Q_OBJECT

public:
    explicit StatisticsTab(QWidget* parent = nullptr);
    ~StatisticsTab();

    void setDictionariesStatistics(const DictionariesStatistics&);

signals:
    void notifyAboutDictionaryStatisticsRequest(const QString& dictionaryName) const;
    void notifyAboutDictionariesStatisticsRequest() const;

public slots:
    void onDictionaryStatisticsReceived(const DictionaryStatistics&);
    void onDictionariesStatisticsReceived(const DictionariesStatistics&);

private slots:
    void on_listOfDictionaries_clicked(const QModelIndex& dictionaryNameIndex);

private:
    void updateCurrentDictionaryStatistics(const DictionaryStatistics&);
    void updateChartView(const DictionaryStatistics&);
    DictionaryStatistics getDictionaryStatistics(const QString& dictionaryName) const;

    DictionariesStatistics dictionariesStatistics;
    QStringListModel dictionaryNames;

    Ui::StatisticsTab* ui;
    std::unique_ptr<QChartView> chartView;
    std::unique_ptr<QChart> chart;
    std::unique_ptr<QPieSeries> pieSeries;
};
}
