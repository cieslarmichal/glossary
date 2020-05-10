#pragma once

#include <QMainWindow>
#include <memory>

#include "view/GuessTab.h"
class DictionariesTab;
class CheckWordDescriptionTab;
class TranslatorTab;
class StatisticsTab;

namespace Ui {
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent, std::unique_ptr<GuessTab>, DictionariesTab&, CheckWordDescriptionTab&, TranslatorTab&, StatisticsTab&);
    ~MainView();

private slots:
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionLoadDictionary_triggered();

private:
    std::unique_ptr<GuessTab> guessTab;
    DictionariesTab& dictionariesTab;
    CheckWordDescriptionTab& checkWordDescriptionTab;
    TranslatorTab& translatorTab;
    StatisticsTab& statisticsTab;

    Ui::MainView *ui;
};

