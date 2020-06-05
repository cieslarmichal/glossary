#include "StatisticsTabViewManager.h"

namespace glossary::gui::viewManager
{
StatisticsTabViewManager::StatisticsTabViewManager(QObject* parent,
                                                   std::shared_ptr<view::StatisticsTab> statisticsTabInit,
                                                   std::shared_ptr<model::GlossaryAdapter> adapter)
    : QObject(parent), statisticsTab{std::move(statisticsTabInit)}, glossaryAdapter{std::move(adapter)}
{
    connect(statisticsTab.get(), &view::StatisticsTab::notifyAboutDictionaryStatisticsRequest,
            glossaryAdapter.get(), &model::GlossaryAdapter::onDictionaryStatisticsRequest);
    connect(statisticsTab.get(), &view::StatisticsTab::notifyAboutDictionariesStatisticsRequest,
            glossaryAdapter.get(), &model::GlossaryAdapter::onDictionariesStatisticsRequest);

    connect(glossaryAdapter.get(), &model::GlossaryAdapter::notifyAboutDictionaryStatistics,
            statisticsTab.get(), &view::StatisticsTab::onDictionaryStatisticsReceived);
    connect(glossaryAdapter.get(), &model::GlossaryAdapter::notifyAboutDictionariesStatistics,
            statisticsTab.get(), &view::StatisticsTab::onDictionariesStatisticsReceived);

    statisticsTab->setDictionariesStatistics(glossaryAdapter->getDictionariesStatistics());
}
}
