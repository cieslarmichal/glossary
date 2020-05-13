#pragma once

#include <QObject>
#include <memory>

#include "view/CheckWordDescriptionTab.h"
#include "model/GlossaryAdapter.h"

namespace glossary::gui::viewManager
{
class CheckWordDescriptionTabViewManager : public QObject
{
    Q_OBJECT
public:
    CheckWordDescriptionTabViewManager(QObject* parent, std::shared_ptr<view::CheckWordDescriptionTab>,
                                       std::shared_ptr<model::GlossaryAdapter>);

private:
    std::shared_ptr<view::CheckWordDescriptionTab> wordDescriptionTab;
    std::shared_ptr<model::GlossaryAdapter> glossaryAdapter;
};
}
