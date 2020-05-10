#include "MainView.h"
#include "ui_MainView.h"
#include "AboutDialog.h"

MainView::MainView(QWidget *parent, std::unique_ptr<GuessTab> guessTabInit, DictionariesTab & dictionatiesTabInit,
                   CheckWordDescriptionTab & checkWordDescriptionTabInit, TranslatorTab & translatorTabInit, StatisticsTab & statisticsTabInit)
    : QMainWindow(parent), guessTab{std::move(guessTabInit)}, dictionariesTab{dictionatiesTabInit},
      checkWordDescriptionTab{checkWordDescriptionTabInit}, translatorTab{translatorTabInit}, statisticsTab{statisticsTabInit}, ui(new Ui::MainView)
{
    ui->setupUi(this);
}

MainView::~MainView()
{
    delete ui;
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

void MainView::on_actionLoadDictionary_triggered()
{

}
