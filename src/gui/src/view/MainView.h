#pragma once

#include <QMainWindow>
#include <memory>

#include "CheckWordDescriptionTab.h"
#include "DictionariesTab.h"
#include "GuessTab.h"
#include "StatisticsTab.h"
#include "TranslatorTab.h"
#include "WelcomeTab.h"

namespace glossary::gui::view
{
namespace Ui
{
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget* parent, std::shared_ptr<WelcomeTab>, std::shared_ptr<GuessTab>,
                      std::shared_ptr<DictionariesTab>, std::shared_ptr<CheckWordDescriptionTab>,
                      std::shared_ptr<TranslatorTab>, std::shared_ptr<StatisticsTab>);
    ~MainView();

public slots:
    void onSetEnabledGuessTabRequest(bool tabEnabled) const;
    void onSetEnabledDictionariesTabRequest(bool tabEnabled) const;
    void onSetEnabledWordDescriptionTabTabRequest(bool tabEnabled) const;
    void onSetEnabledTranslatorTab(bool tabEnabled) const;

private slots:
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionLoadDictionary_triggered();

private:
    std::shared_ptr<WelcomeTab> welcomeTab;
    std::shared_ptr<GuessTab> guessTab;
    std::shared_ptr<DictionariesTab> dictionariesTab;
    std::shared_ptr<CheckWordDescriptionTab> checkWordDescriptionTab;
    std::shared_ptr<TranslatorTab> translatorTab;
    std::shared_ptr<StatisticsTab> statisticsTab;

    Ui::MainView* ui;
};
}
