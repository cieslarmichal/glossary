#include "GuessTabViewManager.h"

namespace glossary::gui::viewManager
{
GuessTabViewManager::GuessTabViewManager(QObject* parent, std::shared_ptr<view::GuessTab> guessTabInit,
                                         std::shared_ptr<model::GlossaryAdapter> adapter)
    : QObject(parent), guessTab{std::move(guessTabInit)}, glossaryAdapter{std::move(adapter)}
{
}
}
