#include "CheckWordDescriptionTabViewManager.h"

#include <utility>

namespace glossary::gui::viewManager
{

CheckWordDescriptionTabViewManager::CheckWordDescriptionTabViewManager(
    QObject* parent, std::shared_ptr<view::CheckWordDescriptionTab> wordDescriptionTabInit,
    std::shared_ptr<model::GlossaryAdapter> adapter)
    : QObject(parent),
      wordDescriptionTab{std::move(wordDescriptionTabInit)},
      glossaryAdapter{std::move(adapter)}
{
    connect(wordDescriptionTab.get(), &view::CheckWordDescriptionTab::notifyCheckWordDescriptionClicked,
            glossaryAdapter.get(), &model::GlossaryAdapter::onWordDescriptionTriggeredFromWordDescriptionTab);
    connect(glossaryAdapter.get(), &model::GlossaryAdapter::notifyWordDescriptionTabAboutWordDescription,
            wordDescriptionTab.get(), &view::CheckWordDescriptionTab::onWordDescriptionReceived);
}

}
