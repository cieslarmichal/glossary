#include "MainViewCreator.h"
#include "view/CheckWordDescriptionTab.h"
#include "view/DictionariesTab.h"
#include "view/GuessTab.h"
#include "view/StatisticsTab.h"
#include "view/TranslatorTab.h"

std::unique_ptr<MainView> MainViewCreator::createMainView()
{
    return std::make_unique<MainView>(nullptr,
                                      std::make_unique<GuessTab>(nullptr),
                                      *new DictionariesTab(nullptr),
                                      *new CheckWordDescriptionTab(nullptr),
                                      *new TranslatorTab(nullptr),
                                      *new StatisticsTab(nullptr));
}
