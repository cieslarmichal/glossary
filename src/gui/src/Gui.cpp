#include "Gui.h"

#include "model/GlossaryAdapter.h"
#include "view/CheckWordDescriptionTab.h"
#include "view/DictionariesTab.h"
#include "view/GuessTab.h"
#include "view/StatisticsTab.h"
#include "view/TranslatorTab.h"

namespace glossary::gui
{
Gui::Gui() : QObject(nullptr)
{
    initialize();
}

void Gui::show() const
{
    mainView->show();
}

void Gui::initialize()
{
    auto guessTab = std::make_shared<view::GuessTab>();
    auto dictionariesTab = std::make_shared<view::DictionariesTab>();
    auto checkWordDescriptionTab = std::make_shared<view::CheckWordDescriptionTab>();
    auto translatorTab = std::make_shared<view::TranslatorTab>();
    auto statisticsTab = std::make_shared<view::StatisticsTab>();
    mainView = std::make_unique<view::MainView>(nullptr, guessTab, dictionariesTab, checkWordDescriptionTab,
                                          translatorTab, statisticsTab);

    auto glossaryAdapter = std::make_shared<model::GlossaryAdapter>();

    guessViewManager = std::make_unique<viewManager::GuessTabViewManager>(this, guessTab, glossaryAdapter);
    dictionariesViewManager =
        std::make_unique<viewManager::DictionariesTabViewManager>(this, dictionariesTab, glossaryAdapter);
    wordDescriptionViewManager =
        std::make_unique<viewManager::CheckWordDescriptionTabViewManager>(this, checkWordDescriptionTab, glossaryAdapter);
    translatorViewManager = std::make_unique<viewManager::TranslatorTabViewManager>(this, translatorTab, glossaryAdapter);
    statisticsViewManager = std::make_unique<viewManager::StatisticsTabViewManager>(this, statisticsTab, glossaryAdapter);
}
}
