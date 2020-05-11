#pragma once

#include <QObject>
#include <memory>

class StatisticsTab;
class GlossaryAdapter;

class StatisticsTabViewManager : public QObject
{
    Q_OBJECT
public:
    StatisticsTabViewManager(QObject *parent, std::shared_ptr<StatisticsTab>, std::shared_ptr<GlossaryAdapter>);

private:
     std::shared_ptr<StatisticsTab> statisticsTab;
     std::shared_ptr<GlossaryAdapter> glossaryAdapter;
};

