#include "TranslatorTabViewManager.h"

namespace glossary::gui::viewManager
{
TranslatorTabViewManager::TranslatorTabViewManager(QObject* parent,
                                                   std::shared_ptr<view::TranslatorTab> translatorTabInit,
                                                   std::shared_ptr<model::GlossaryAdapter> adapter)
    : QObject(parent), translatorTab{std::move(translatorTabInit)}, glossaryAdapter{std::move(adapter)}
{
    connect(translatorTab.get(), &view::TranslatorTab::notifyAboutTextTranslateRequest, glossaryAdapter.get(),
            &model::GlossaryAdapter::onTextTranslateRequest);
    connect(glossaryAdapter.get(), &model::GlossaryAdapter::notifyAboutTranslation, translatorTab.get(),
            &view::TranslatorTab::onTranslationReceived);

    connect(translatorTab.get(), &view::TranslatorTab::notifyAboutAvailableLanguagesRequest,
            glossaryAdapter.get(), &model::GlossaryAdapter::onTranslatorAvailableLanguagesRequest);
    connect(glossaryAdapter.get(), &model::GlossaryAdapter::notifyAboutAvailableLanguages,
            translatorTab.get(), &view::TranslatorTab::onAvailableLanguagesReceived);

    translatorTab->setAvailableLanguages(glossaryAdapter->getAvailableLanguages());
}
}
