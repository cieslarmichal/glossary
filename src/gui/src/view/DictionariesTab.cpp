#include "DictionariesTab.h"

#include "ui_DictionariesTab.h"

namespace glossary::gui::view
{
DictionariesTab::DictionariesTab(QWidget* parent) : QWidget(parent), ui(new Ui::DictionariesTab)
{
    ui->setupUi(this);
    ui->listOfDictionaries->setModel(&currentDictionaryNames);
}

DictionariesTab::~DictionariesTab()
{
    delete ui;
}

void DictionariesTab::setDictionaries(const Dictionaries& dictionaries)
{
    auto formattedDictionaries = dictionaryFormatter.getFormattedDictionaries(dictionaries);
    currentDictionaries.updateDictionaries(formattedDictionaries);
    synchronizeDictionariesModels();
}

void DictionariesTab::onDictionaryWordsUpdate(const DictionaryName & dictionaryName, const DictionaryWords & dictionaryWords)
{
    auto formattedDictionaryName = dictionaryFormatter.getFormattedDictionaryName(dictionaryName);
    auto formattedDictionaryWords = dictionaryFormatter.getFormattedDictionaryWords(dictionaryWords);
    currentDictionaries.updateDictionaryWords(formattedDictionaryName, formattedDictionaryWords);
}

void DictionariesTab::onDictionariesUpdate(const Dictionaries & dictionaries)
{
    auto formattedDictionaries = dictionaryFormatter.getFormattedDictionaries(dictionaries);
    currentDictionaries.updateDictionaries(formattedDictionaries);
}

void DictionariesTab::on_buttonAddNewDictionary_clicked()
{

}

void DictionariesTab::on_buttonAddDictionaryFromFile_clicked()
{

}

void DictionariesTab::on_buttonRemoveDictionary_clicked()
{

}

void DictionariesTab::on_buttonUpdateTranslations_clicked()
{

}

void DictionariesTab::on_buttonAddWord_clicked()
{
    
}

void DictionariesTab::on_buttonModifyWord_clicked()
{
    
}

void DictionariesTab::on_buttonUpdateTranslation_clicked()
{
    
}

void DictionariesTab::on_buttonRemoveWord_clicked()
{
    
}

void DictionariesTab::synchronizeDictionariesModels()
{
    currentDictionaryNames.setStringList(currentDictionaries.getDictionaryNames());
}

}
