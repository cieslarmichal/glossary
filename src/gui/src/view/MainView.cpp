#include "MainView.h"

#include <utility>

#include "AboutDialog.h"
#include "ui_MainView.h"

namespace glossary::gui::view
{
namespace
{
constexpr int guessTabIndex = 1;
constexpr int dictionariesTabIndex = 2;
constexpr int wordDescriptionTabIndex = 3;
constexpr int translatorTabIndex = 4;
}

MainView::MainView(QWidget* parent, std::shared_ptr<WelcomeTab> welcomeTabInit,
                   std::shared_ptr<GuessTab> guessTabInit,
                   std::shared_ptr<DictionariesTab> dictionatiesTabInit,
                   std::shared_ptr<CheckWordDescriptionTab> checkWordDescriptionTabInit,
                   std::shared_ptr<TranslatorTab> translatorTabInit,
                   std::shared_ptr<StatisticsTab> statisticsTabInit)
    : QMainWindow(parent),
      welcomeTab{std::move(welcomeTabInit)},
      guessTab{std::move(guessTabInit)},
      dictionariesTab{std::move(dictionatiesTabInit)},
      checkWordDescriptionTab{std::move(checkWordDescriptionTabInit)},
      translatorTab{std::move(translatorTabInit)},
      statisticsTab{std::move(statisticsTabInit)},
      ui(new Ui::MainView)
{
    ui->setupUi(this);
    welcomeTab->setParent(this);
    guessTab->setParent(this);
    dictionariesTab->setParent(this);
    checkWordDescriptionTab->setParent(this);
    translatorTab->setParent(this);
    statisticsTab->setParent(this);
    ui->welcomeTabLayout->addWidget(welcomeTab.get());
    ui->guessTabLayout->addWidget(guessTab.get());
    ui->dictionariesTabLayout->addWidget(dictionariesTab.get());
    ui->wordDescriptionTabLayout->addWidget(checkWordDescriptionTab.get());
    ui->translatorTabLayout->addWidget(translatorTab.get());
    ui->statisticsTabLayout->addWidget(statisticsTab.get());

    connect(welcomeTab.get(), &WelcomeTab::notifyAboutSetGuessTabEnabledRequest, this,
            &MainView::onSetEnabledGuessTabRequest);
    connect(welcomeTab.get(), &WelcomeTab::notifyAboutSetDictionariesTabEnabledRequest, this,
            &MainView::onSetEnabledDictionariesTabRequest);
    connect(welcomeTab.get(), &WelcomeTab::notifyAboutSetWordDescriptionTabEnabledRequest, this,
            &MainView::onSetEnabledWordDescriptionTabTabRequest);
    connect(welcomeTab.get(), &WelcomeTab::notifyAboutSetTranslatorTabEnabledRequest, this,
            &MainView::onSetEnabledTranslatorTab);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::onSetEnabledGuessTabRequest(bool tabEnabled) const
{
    ui->glossaryModesTabs->setTabEnabled(guessTabIndex, tabEnabled);
}

void MainView::onSetEnabledDictionariesTabRequest(bool tabEnabled) const
{
    ui->glossaryModesTabs->setTabEnabled(dictionariesTabIndex, tabEnabled);
}

void MainView::onSetEnabledWordDescriptionTabTabRequest(bool tabEnabled) const
{
    ui->glossaryModesTabs->setTabEnabled(wordDescriptionTabIndex, tabEnabled);
}

void MainView::onSetEnabledTranslatorTab(bool tabEnabled) const
{
    ui->glossaryModesTabs->setTabEnabled(translatorTabIndex, tabEnabled);
}

void MainView::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainView::on_actionAbout_triggered()
{
    AboutDialog aboutBox;
    aboutBox.show();
    aboutBox.exec();
}

void MainView::on_actionLoadDictionary_triggered() {}

}
