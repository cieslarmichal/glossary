#include "DictionariesTabViewManager.h"

namespace glossary::gui::viewManager
{
DictionariesTabViewManager::DictionariesTabViewManager(
    QObject* parent, std::shared_ptr<view::DictionariesTab> dictionariesTabInit,
    std::shared_ptr<model::GlossaryAdapter> adapter)
    : QObject(parent), dictionariesTab{std::move(dictionariesTabInit)}, glossaryAdapter{std::move(adapter)}
{
}
}
