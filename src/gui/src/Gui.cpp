#include "Gui.h"

#include "../../common/fileSystem/include/GetProjectPath.h"
#include "GlossaryFactory.h"
#include "model/GlossaryAdapter.h"
#include "view/CheckWordDescriptionTab.h"
#include "view/DictionariesTab.h"
#include "view/GuessTab.h"
#include "view/StatisticsTab.h"
#include "view/TranslatorTab.h"
#include "view/WelcomeTab.h"

namespace glossary::gui
{
namespace
{
const auto resourceDirectoryPath = common::getProjectPath("glossary") + "src/gui/resources/";
const auto glossaryIconPath = resourceDirectoryPath + "glossaryIcon.png";
}

Gui::Gui(QApplication& applicationInit) : QObject(nullptr), application{applicationInit}
{
    initialize();
}

void Gui::show() const
{
    mainView->show();
}

void Gui::initialize()
{
    application.setWindowIcon(QIcon(glossaryIconPath.c_str()));

    auto welcomeTab = std::make_shared<view::WelcomeTab>();
    auto guessTab = std::make_shared<view::GuessTab>();
    auto dictionariesTab = std::make_shared<view::DictionariesTab>();
    auto checkWordDescriptionTab = std::make_shared<view::CheckWordDescriptionTab>();
    auto translatorTab = std::make_shared<view::TranslatorTab>();
    auto statisticsTab = std::make_shared<view::StatisticsTab>();
    mainView = std::make_unique<view::MainView>(nullptr, welcomeTab, guessTab, dictionariesTab,
                                                checkWordDescriptionTab, translatorTab, statisticsTab);

    auto glossaryAdapter =
        std::make_shared<model::GlossaryAdapter>(GlossaryFactory::createGlossaryFactory()->createGlossary());

    welcomeViewManager =
        std::make_unique<viewManager::WelcomeTabViewManager>(this, welcomeTab, glossaryAdapter);
    guessViewManager = std::make_unique<viewManager::GuessTabViewManager>(this, guessTab, glossaryAdapter);
    dictionariesViewManager =
        std::make_unique<viewManager::DictionariesTabViewManager>(this, dictionariesTab, glossaryAdapter);
    wordDescriptionViewManager = std::make_unique<viewManager::CheckWordDescriptionTabViewManager>(
        this, checkWordDescriptionTab, glossaryAdapter);
    translatorViewManager =
        std::make_unique<viewManager::TranslatorTabViewManager>(this, translatorTab, glossaryAdapter);
    statisticsViewManager =
        std::make_unique<viewManager::StatisticsTabViewManager>(this, statisticsTab, glossaryAdapter);
}
}
