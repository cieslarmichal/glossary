#include "DictionariesTab.h"

#include <QDir>
#include <QFileDialog>

#include "AddDictionaryDialog.h"
#include "AddDictionaryWordDialog.h"
#include "ui_DictionariesTab.h"

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

void DictionariesTab::setDictionaries(const std::vector<dictionary::Dictionary>& dictionaries)
{
    auto formattedDictionaries = dictionaryFormatter.getFormattedDictionaries(dictionaries);

    dictionariesStorage.updateDictionaries(formattedDictionaries);

    synchronizeDictionariesModel();
}

void DictionariesTab::onDictionaryWordsUpdate(const std::string& dictionaryName,
                                              const std::vector<dictionary::DictionaryWord>& dictionaryWords)
{
    auto formattedDictionaryName = dictionaryFormatter.getFormattedDictionaryName(dictionaryName);

    auto formattedDictionaryWords = dictionaryFormatter.getFormattedDictionaryWords(dictionaryWords);

    dictionariesStorage.updateDictionaryWords(formattedDictionaryName, formattedDictionaryWords);

    synchronizeDictionaryWordsModel(QString::fromStdString(dictionaryName));
}

void DictionariesTab::onDictionariesUpdate(const std::vector<dictionary::Dictionary>& dictionaries)
{
    auto formattedDictionaries = dictionaryFormatter.getFormattedDictionaries(dictionaries);

    dictionariesStorage.updateDictionaries(formattedDictionaries);

    synchronizeDictionariesModel();
}

void DictionariesTab::on_buttonAddNewDictionary_clicked()
{
    AddDictionaryDialog addDictionaryPrompt;

    addDictionaryPrompt.show();

    if (addDictionaryPrompt.exec() == QDialog::Accepted)
    {
        auto addedDictionaryName = addDictionaryPrompt.getDictionaryName();
        emit notifyAddNewDictionary(addedDictionaryName);
    }
}

void DictionariesTab::on_buttonAddDictionaryFromFile_clicked()
{
    auto pathToDictionaryWords = QFileDialog::getOpenFileName(this, "Open file with dictionary words");
    auto dictionaryFileName = QFileInfo{pathToDictionaryWords}.fileName();
    QString dictionaryName = dictionaryFileName.section(".", 0, 0);
    emit notifyAddDictionaryFromFile(dictionaryName, pathToDictionaryWords);
}

void DictionariesTab::on_buttonRemoveDictionary_clicked()
{
    if (currentDictionaryName)
    {
        emit notifyRemoveDictionary(*currentDictionaryName);
        currentDictionaryName = std::nullopt;
        currentEnglishWord = std::nullopt;
        setDictionaryButtonsEnabled(false);
        setDictionaryWordsNoFocusButtonsEnabled(false);
        setDictionaryWordsWithFocusButtonsEnabled(false);
    }
}

void DictionariesTab::on_buttonUpdateTranslations_clicked()
{
    if (currentDictionaryName)
    {
        emit notifyUpdateDictionaryTranslationsRequest(*currentDictionaryName);
    }
}

void DictionariesTab::on_buttonAddWord_clicked()
{
    AddDictionaryWordDialog addDictionaryWordPrompt;

    addDictionaryWordPrompt.show();

    if (addDictionaryWordPrompt.exec() == QDialog::Accepted)
    {
        auto addedEnglishWord = addDictionaryWordPrompt.getEnglishWord();

        auto addedTranslation = addDictionaryWordPrompt.getTranslation();

        if (addedTranslation.isEmpty() && currentDictionaryName)
        {
            emit notifyAddWordWithoutTranslation(*currentDictionaryName, addedEnglishWord);
        }
        else
        {
            emit notifyAddWordWithTranslation(*currentDictionaryName, addedEnglishWord, addedTranslation);
        }
    }

    setDictionaryWordsWithFocusButtonsEnabled(false);

    currentEnglishWord = std::nullopt;
}

void DictionariesTab::on_buttonUpdateTranslation_clicked()
{
    if (currentDictionaryName && currentEnglishWord)
    {
        emit notifyUpdateTranslationRequest(*currentDictionaryName, *currentEnglishWord);
    }

    setDictionaryWordsWithFocusButtonsEnabled(false);

    currentEnglishWord = std::nullopt;
}

void DictionariesTab::on_buttonRemoveWord_clicked()
{
    if (currentDictionaryName && currentEnglishWord)
    {
        emit notifyRemoveWord(*currentDictionaryName, *currentEnglishWord);

        currentEnglishWord = std::nullopt;
    }

    setDictionaryWordsWithFocusButtonsEnabled(false);

    currentEnglishWord = std::nullopt;
}

void DictionariesTab::synchronizeDictionariesModel()
{
    if (dictionariesStorage.dictionariesAreEmpty())
    {
        setDictionaryButtonsEnabled(false);
    }
    else
    {
        dictionaryNames.setStringList(dictionariesStorage.getDictionaryNames());

        if (currentDictionaryName)
        {
            synchronizeDictionaryWordsModel(*currentDictionaryName);
        }
        else
        {
            clearDictionaryWordsModel();
        }
    }
}

void DictionariesTab::synchronizeDictionaryWordsModel(const QString& dictionaryName)
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

void DictionariesTab::on_listOfDictionaries_clicked(const QModelIndex& dictionaryNameIndex)
{
    QString dictionaryName = dictionaryNameIndex.data(Qt::DisplayRole).toString();

    currentDictionaryName = dictionaryName;

    currentEnglishWord = std::nullopt;

    synchronizeDictionaryWordsModel(dictionaryName);

    setDictionaryButtonsEnabled(true);

    setDictionaryWordsNoFocusButtonsEnabled(true);

    setDictionaryWordsWithFocusButtonsEnabled(false);
}

void DictionariesTab::on_listOfDictionaryWords_clicked(const QModelIndex& dictionaryWordIndex)
{
    QString dictionaryWordAccumulated = dictionaryWordIndex.data(Qt::DisplayRole).toString();

    if (const auto dictionaryWord =
            dictionaryWordAccumulator.separateDictionaryWord(dictionaryWordAccumulated))
    {
        currentEnglishWord = dictionaryWord->englishWord;

        setDictionaryWordsWithFocusButtonsEnabled(true);
    }
}

}
