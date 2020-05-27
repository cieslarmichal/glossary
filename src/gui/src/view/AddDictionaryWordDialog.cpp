#include "AddDictionaryWordDialog.h"

#include "ui_AddDictionaryWordDialog.h"

namespace glossary::gui::view
{
AddDictionaryWordDialog::AddDictionaryWordDialog() : QDialog(nullptr), ui(new Ui::AddDictionaryWordDialog)
{
    ui->setupUi(this);
}

AddDictionaryWordDialog::~AddDictionaryWordDialog()
{
    delete ui;
}

QString AddDictionaryWordDialog::getEnglishWord() const
{
    return englishWord;
}

QString AddDictionaryWordDialog::getTranslation() const
{
    return translation;
}

void AddDictionaryWordDialog::on_editEnglishWord_editingFinished()
{
    englishWord = ui->editEnglishWord->text();
}

void AddDictionaryWordDialog::on_editTranslation_editingFinished()
{
    translation = ui->editTranslation->text();
}
}
