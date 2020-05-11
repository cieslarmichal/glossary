#include "Gui.h"

#include "view/CheckWordDescriptionTab.h"
#include "view/DictionariesTab.h"
#include "view/GuessTab.h"
#include "view/StatisticsTab.h"
#include "view/TranslatorTab.h"

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
    auto guessTab = std::make_unique<GuessTab>();
    auto dictionariesTab =std::make_unique<DictionariesTab>();
    auto checkWordDescriptionTab = std::make_unique<CheckWordDescriptionTab>();
    auto translatorTab = std::make_unique<TranslatorTab>();
    auto statisticsTab = std::make_unique<StatisticsTab>();
    mainView = std::make_unique<MainView>(nullptr, std::move(guessTab),
                                          std::move(dictionariesTab), std::move(checkWordDescriptionTab),
                                          std::move(translatorTab), std::move(statisticsTab));
}
