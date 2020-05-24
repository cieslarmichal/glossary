#include "DictionariesTab.h"

#include "ui_DictionariesTab.h"

namespace glossary::gui::view
{
DictionariesTab::DictionariesTab(QWidget* parent) : QWidget(parent), ui(new Ui::DictionariesTab)
{
    ui->setupUi(this);
}

DictionariesTab::~DictionariesTab()
{
    delete ui;
}


void DictionariesTab::on_buttonAddNewDictionary_clicked()
{

}

void DictionariesTab::on_buttonAddDictionaryFromFile_clicked()
{

}

void DictionariesTab::on_butonRemoveDictionary_clicked()
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
}
