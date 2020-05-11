#pragma once

#include <QMainWindow>
#include <memory>

#include "view/GuessTab.h"
#include "view/CheckWordDescriptionTab.h"
#include "view/DictionariesTab.h"
#include "view/StatisticsTab.h"
#include "view/TranslatorTab.h"

namespace Ui {
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent, std::unique_ptr<GuessTab>, std::unique_ptr<DictionariesTab>,
                      std::unique_ptr<CheckWordDescriptionTab>, std::unique_ptr<TranslatorTab>, std::unique_ptr<StatisticsTab>);
    ~MainView();

private slots:
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionLoadDictionary_triggered();

private:
    std::unique_ptr<GuessTab> guessTab;
    std::unique_ptr<DictionariesTab> dictionariesTab;
    std::unique_ptr<CheckWordDescriptionTab> checkWordDescriptionTab;
    std::unique_ptr<TranslatorTab> translatorTab;
    std::unique_ptr<StatisticsTab> statisticsTab;

    Ui::MainView *ui;
};

