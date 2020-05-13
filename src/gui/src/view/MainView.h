#pragma once

#include <QMainWindow>
#include <memory>

#include "view/CheckWordDescriptionTab.h"
#include "view/DictionariesTab.h"
#include "view/GuessTab.h"
#include "view/StatisticsTab.h"
#include "view/TranslatorTab.h"

namespace Ui
{
class MainView;
}

namespace glossary::gui::view
{
class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget* parent, std::shared_ptr<GuessTab>, std::shared_ptr<DictionariesTab>,
                      std::shared_ptr<CheckWordDescriptionTab>, std::shared_ptr<TranslatorTab>,
                      std::shared_ptr<StatisticsTab>);
    ~MainView();

private slots:
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionLoadDictionary_triggered();

private:
    std::shared_ptr<GuessTab> guessTab;
    std::shared_ptr<DictionariesTab> dictionariesTab;
    std::shared_ptr<CheckWordDescriptionTab> checkWordDescriptionTab;
    std::shared_ptr<TranslatorTab> translatorTab;
    std::shared_ptr<StatisticsTab> statisticsTab;

    Ui::MainView* ui;
};
}
