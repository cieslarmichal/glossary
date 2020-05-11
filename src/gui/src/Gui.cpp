#include "Gui.h"

#include "view/CheckWordDescriptionTab.h"
#include "view/DictionariesTab.h"
#include "view/GuessTab.h"
#include "view/StatisticsTab.h"
#include "view/TranslatorTab.h"
#include "model/GlossaryAdapter.h"

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
    auto guessTab = std::make_shared<GuessTab>();
    auto dictionariesTab =std::make_shared<DictionariesTab>();
    auto checkWordDescriptionTab = std::make_shared<CheckWordDescriptionTab>();
    auto translatorTab = std::make_shared<TranslatorTab>();
    auto statisticsTab = std::make_shared<StatisticsTab>();
    mainView = std::make_unique<MainView>(nullptr, guessTab,
                                          dictionariesTab, checkWordDescriptionTab,
                                          translatorTab, statisticsTab);

    auto glossaryAdapter = std::make_shared<GlossaryAdapter>();

    guessViewManager = std::make_unique<GuessTabViewManager>(this, guessTab, glossaryAdapter);
    dictionariesViewManager = std::make_unique<DictionariesTabViewManager>(this, dictionariesTab, glossaryAdapter);
    wordDescriptionViewManager = std::make_unique<CheckWordDescriptionTabViewManager>(this, checkWordDescriptionTab, glossaryAdapter);
    translatorViewManager = std::make_unique<TranslatorTabViewManager>(this, translatorTab, glossaryAdapter);
    statisticsViewManager = std::make_unique<StatisticsTabViewManager>(this, statisticsTab, glossaryAdapter);
}
