#pragma once

#include "view/MainView.h"
#include "viewManager/CheckWordDescriptionTabViewManager.h"
#include "viewManager/DictionariesTabViewManager.h"
#include "viewManager/GuessTabViewManager.h"
#include "viewManager/StatisticsTabViewManager.h"
#include "viewManager/TranslatorTabViewManager.h"
#include <memory>

#include <QObject>

class Gui : public QObject
{
    Q_OBJECT
public:
    explicit Gui();

    void show() const;

private:
    void initialize();

    std::unique_ptr<MainView> mainView;
    std::unique_ptr<GuessTabViewManager> guessViewManager;
    std::unique_ptr<DictionariesTabViewManager> dictionariesViewManager;
    std::unique_ptr<CheckWordDescriptionTabViewManager> wordDescriptionViewManager;
    std::unique_ptr<TranslatorTabViewManager> translatorViewManager;
    std::unique_ptr<StatisticsTabViewManager> statisticsViewManager;

};

