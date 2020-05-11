#include "StatisticsTabViewManager.h"

StatisticsTabViewManager::StatisticsTabViewManager(QObject *parent, std::shared_ptr<StatisticsTab> statisticsTabInit, std::shared_ptr<GlossaryAdapter> adapter)
    : QObject(parent), statisticsTab{std::move(statisticsTabInit)}, glossaryAdapter{std::move(adapter)}
{

}
