#pragma once

#include <QObject>
#include <memory>

#include "view/MainView.h"
#include "viewManager/CheckWordDescriptionTabViewManager.h"
#include "viewManager/DictionariesTabViewManager.h"
#include "viewManager/GuessTabViewManager.h"
#include "viewManager/StatisticsTabViewManager.h"
#include "viewManager/TranslatorTabViewManager.h"
#include "viewManager/WelcomeTabViewManager.h"

namespace glossary::gui
{
class Gui : public QObject
{
    Q_OBJECT
public:
    explicit Gui();

    void show() const;

private:
    void initialize();

    std::unique_ptr<view::MainView> mainView;
    std::unique_ptr<viewManager::WelcomeTabViewManager> welcomeViewManager;
    std::unique_ptr<viewManager::GuessTabViewManager> guessViewManager;
    std::unique_ptr<viewManager::DictionariesTabViewManager> dictionariesViewManager;
    std::unique_ptr<viewManager::CheckWordDescriptionTabViewManager> wordDescriptionViewManager;
    std::unique_ptr<viewManager::TranslatorTabViewManager> translatorViewManager;
    std::unique_ptr<viewManager::StatisticsTabViewManager> statisticsViewManager;
};
}
