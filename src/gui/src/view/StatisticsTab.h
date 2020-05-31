#pragma once

#include <QChartView>
#include <QWidget>

#include "DictionaryStatistics.h"
QT_CHARTS_USE_NAMESPACE

namespace glossary::gui::view
{
namespace Ui
{
class StatisticsTab;
}

class StatisticsTab : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsTab(QWidget* parent = nullptr);
    ~StatisticsTab();

    //    void setAvailableLanguages(const QStringList&);

signals:
    void notifyAboutDictionaryStatisticsRequest(const QString& dictionaryName) const;
    void notifyAboutDictionariesStatisticsRequest() const;

public slots:
    void onDictionaryStatisticsReceived(const DictionaryStatistics&);
    void onDictionariesStatisticsReceived(const DictionariesStatistics&);

private:
    Ui::StatisticsTab* ui;

    QChartView* chartView;
};
}
