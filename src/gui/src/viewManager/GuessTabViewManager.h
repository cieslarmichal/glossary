#pragma once

#include <QObject>
#include <memory>
#include "view/GuessTab.h"
#include "model/GlossaryAdapter.h"

namespace glossary::gui::viewManager
{
class GuessTabViewManager : public QObject
{
    Q_OBJECT
public:
    GuessTabViewManager(QObject* parent, std::shared_ptr<view::GuessTab>, std::shared_ptr<model::GlossaryAdapter>);

private:
    std::shared_ptr<view::GuessTab> guessTab;
    std::shared_ptr<model::GlossaryAdapter> glossaryAdapter;
};
}
