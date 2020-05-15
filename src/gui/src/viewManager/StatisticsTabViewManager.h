#pragma once

#include <QObject>
#include <memory>

#include "model/GlossaryAdapter.h"
#include "view/StatisticsTab.h"

namespace glossary::gui::viewManager
{
class StatisticsTabViewManager : public QObject
{
    Q_OBJECT
public:
    StatisticsTabViewManager(QObject* parent, std::shared_ptr<view::StatisticsTab>,
                             std::shared_ptr<model::GlossaryAdapter>);

private:
    std::shared_ptr<view::StatisticsTab> statisticsTab;
    std::shared_ptr<model::GlossaryAdapter> glossaryAdapter;
};
}
