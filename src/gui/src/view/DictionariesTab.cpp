#include "DictionariesTab.h"

#include "ui_DictionariesTab.h"
#include "AddDictionaryPrompt.h"
#include "AddDictionaryWordPrompt.h"
#include <QFileDialog>

namespace glossary::gui::view
{

DictionariesTab::DictionariesTab(QWidget* parent) : QWidget(parent), ui(new Ui::DictionariesTab)
{
    ui->setupUi(this);
    ui->listOfDictionaries->setModel(&dictionaryNames);
    ui->listOfDictionaryWords->setModel(&currentDctionaryWords);
    setDictionaryButtonsEnabled(false);
    setDictionaryWordsNoFocusButtonsEnabled(false);
    setDictionaryWordsWithFocusButtonsEnabled(false);
}

DictionariesTab::~DictionariesTab()
{
    delete ui;
}

void DictionariesTab::setDictionaries(const Dictionaries& dictionaries)
{
    auto formattedDictionaries = dictionaryFormatter.getFormattedDictionaries(dictionaries);
    dictionariesStorage.updateDictionaries(formattedDictionaries);
    synchronizeDictionariesModel();
}

void DictionariesTab::onDictionaryWordsUpdate(const DictionaryName & dictionaryName, const DictionaryWords & dictionaryWords)
{
    auto formattedDictionaryName = dictionaryFormatter.getFormattedDictionaryName(dictionaryName);
    auto formattedDictionaryWords = dictionaryFormatter.getFormattedDictionaryWords(dictionaryWords);
    dictionariesStorage.updateDictionaryWords(formattedDictionaryName, formattedDictionaryWords);
    synchronizeDictionaryWordsModel(QString::fromStdString(dictionaryName));
}

void DictionariesTab::onDictionariesUpdate(const Dictionaries & dictionaries)
{
    auto formattedDictionaries = dictionaryFormatter.getFormattedDictionaries(dictionaries);
    dictionariesStorage.updateDictionaries(formattedDictionaries);
    synchronizeDictionariesModel();
}

void DictionariesTab::on_buttonAddNewDictionary_clicked()
{
    AddDictionaryPrompt addDictionaryPrompt;
    addDictionaryPrompt.show();
    if(addDictionaryPrompt.exec() == QDialog::Accepted)
    {
        auto addedDictionaryName = addDictionaryPrompt.getDictionaryName();
        emit notifyAddNewDictionary(addedDictionaryName);
    }
}

void DictionariesTab::on_buttonAddDictionaryFromFile_clicked()
{
    QString fileWithDictionaryWords = QFileDialog::getSaveFileName(this, "Open file with dictionary words");
}

void DictionariesTab::on_buttonRemoveDictionary_clicked()
{
    if(currentDictionaryName)
    {
        emit notifyRemoveDictionary(*currentDictionaryName);
        currentDictionaryName = boost::none;
        currentDictionaryWord = boost::none;
        setDictionaryButtonsEnabled(false);
        setDictionaryWordsNoFocusButtonsEnabled(false);
        setDictionaryWordsWithFocusButtonsEnabled(false);
    }
}

void DictionariesTab::on_buttonUpdateTranslations_clicked()
{
    if(currentDictionaryName)
    {
        emit notifyUpdateDictionaryTranslationsRequest(*currentDictionaryName);
    }
}

void DictionariesTab::on_buttonAddWord_clicked()
{
    AddDictionaryWordPrompt addDictionaryWordPrompt;
    addDictionaryWordPrompt.show();
    if(addDictionaryWordPrompt.exec() == QDialog::Accepted)
    {
        auto addedEnglishWord = addDictionaryWordPrompt.getEnglishWord();
        auto addedTranlsation = addDictionaryWordPrompt.getTranslation();
        if(addedTranlsation.isEmpty() && currentDictionaryName)
        {
            emit notifyAddWordWithoutTranslation(*currentDictionaryName, addedEnglishWord);
        }
        else
        {
            emit notifyAddWordWithTranslation(*currentDictionaryName, addedEnglishWord, addedTranlsation);
        }
    }
    setDictionaryWordsWithFocusButtonsEnabled(false);
    currentDictionaryWord = boost::none;
}

void DictionariesTab::on_buttonUpdateTranslation_clicked()
{
    if(currentDictionaryName && currentDictionaryWord)
    {
        emit notifyUpdateTranslationRequest(*currentDictionaryName, *currentDictionaryWord);
    }
    setDictionaryWordsWithFocusButtonsEnabled(false);
    currentDictionaryWord =boost::none;
}

void DictionariesTab::on_buttonRemoveWord_clicked()
{
    if(currentDictionaryName && currentDictionaryWord)
    {
        // TODO: handle englishword - translation
        emit notifyRemoveWord(*currentDictionaryName, *currentDictionaryWord);
        currentDictionaryWord = boost::none;
    }
    setDictionaryWordsWithFocusButtonsEnabled(false);
    currentDictionaryWord =boost::none;
}

void DictionariesTab::synchronizeDictionariesModel()
{
    if(dictionariesStorage.dictionariesAreEmpty())
    {
        setDictionaryButtonsEnabled(false);
    }
    else
    {
        dictionaryNames.setStringList(dictionariesStorage.getDictionaryNames());
        if(currentDictionaryName)
        {
            synchronizeDictionaryWordsModel(*currentDictionaryName);
        }
        else
        {
            clearDictionaryWordsModel();
        }
    }
}

void DictionariesTab::synchronizeDictionaryWordsModel(const QString &dictionaryName)
{
    auto formattedDictionaryWords = dictionariesStorage.getDictionaryWords(dictionaryName);
    auto accumulatedDictionaryWords = getAccumulatedFormattedDictionaryWords(formattedDictionaryWords);
    currentDctionaryWords.setStringList(accumulatedDictionaryWords);
}

void DictionariesTab::clearDictionaryWordsModel()
{
    currentDctionaryWords.setStringList({});
}

void DictionariesTab::setDictionaryWordsNoFocusButtonsEnabled(bool enabled)
{
    ui->buttonAddWord->setEnabled(enabled);
}

void DictionariesTab::setDictionaryWordsWithFocusButtonsEnabled(bool enabled)
{
    ui->buttonUpdateTranslation->setEnabled(enabled);
    ui->buttonRemoveWord->setEnabled(enabled);
}

void DictionariesTab::setDictionaryButtonsEnabled(bool enabled)
{
    ui->buttonRemoveDictionary->setEnabled(enabled);
    ui->buttonUpdateTranslations->setEnabled(enabled);
}

void DictionariesTab::on_listOfDictionaries_clicked(const QModelIndex & dictionaryNameIndex)
{
    QString dictionaryName = dictionaryNameIndex.data(Qt::DisplayRole).toString();
    currentDictionaryName = dictionaryName;
    currentDictionaryWord = boost::none;
    synchronizeDictionaryWordsModel(dictionaryName);

    setDictionaryButtonsEnabled(true);
    setDictionaryWordsNoFocusButtonsEnabled(true);
    setDictionaryWordsWithFocusButtonsEnabled(false);
}

void DictionariesTab::on_listOfDictionaryWords_clicked(const QModelIndex &dictionaryWordIndex)
{
    QString dictionaryWord = dictionaryWordIndex.data(Qt::DisplayRole).toString();
    currentDictionaryWord = dictionaryWord;
    setDictionaryWordsWithFocusButtonsEnabled(true);
}

}

