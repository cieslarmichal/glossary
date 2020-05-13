#include "StatisticsTabViewManager.h"

namespace glossary::gui::viewManager
{
StatisticsTabViewManager::StatisticsTabViewManager(QObject* parent,
                                                   std::shared_ptr<view::StatisticsTab> statisticsTabInit,
                                                   std::shared_ptr<model::GlossaryAdapter> adapter)
    : QObject(parent), statisticsTab{std::move(statisticsTabInit)}, glossaryAdapter{std::move(adapter)}
{
}
}
