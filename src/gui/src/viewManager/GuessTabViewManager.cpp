#include "GuessTabViewManager.h"

#include <QStringListModel>

namespace glossary::gui::viewManager
{
GuessTabViewManager::GuessTabViewManager(QObject* parent, std::shared_ptr<view::GuessTab> guessTabInit,
                                         std::shared_ptr<model::GlossaryAdapter> adapter)
    : QObject(parent), guessTab{std::move(guessTabInit)}, glossaryAdapter{std::move(adapter)}
{
    connect(guessTab.get(), &view::GuessTab::notifyNextRandomWordClicked, glossaryAdapter.get(),
            &model::GlossaryAdapter::onRandomPolishWordTriggered);
    connect(guessTab.get(), &view::GuessTab::notifyNextRandomWordFromDictionaryClicked, glossaryAdapter.get(),
            &model::GlossaryAdapter::onRandomPolishWordFromDictionaryTriggered);
    connect(glossaryAdapter.get(), &model::GlossaryAdapter::notifyAboutRandomPolishWord, guessTab.get(),
            &view::GuessTab::onNextRandomWordReceived);

    connect(guessTab.get(), &view::GuessTab::notifyCheckWordDescriptionClicked, glossaryAdapter.get(),
            &model::GlossaryAdapter::onWordDescriptionTriggeredFromGuessTab);
    connect(glossaryAdapter.get(), &model::GlossaryAdapter::notifyGuessTabAboutWordDescription,
            guessTab.get(), &view::GuessTab::onWordDescriptionReceived);

    connect(guessTab.get(), &view::GuessTab::notifyCheckTranslationCorrectnessClicked, glossaryAdapter.get(),
            &model::GlossaryAdapter::onTranslationCorrectnessTriggered);
    connect(glossaryAdapter.get(), &model::GlossaryAdapter::notifyAboutTranslationVerdict, guessTab.get(),
            &view::GuessTab::onCheckedTranslationVerdictReceived);

    guessTab->setAvailableDictionaryNames(glossaryAdapter->getDictionaryNames());
}
}
