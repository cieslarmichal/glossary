#include "TranslatorTabViewManager.h"

namespace glossary::gui::viewManager
{
TranslatorTabViewManager::TranslatorTabViewManager(QObject* parent,
                                                   std::shared_ptr<view::TranslatorTab> translatorTabInit,
                                                   std::shared_ptr<model::GlossaryAdapter> adapter)
    : QObject(parent), translatorTab{std::move(translatorTabInit)}, glossaryAdapter{std::move(adapter)}
{
}
}
