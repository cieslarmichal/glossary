#include "AddDictionaryWordPrompt.h"
#include "ui_AddDictionaryWordPrompt.h"

namespace glossary::gui::view
{
AddDictionaryWordPrompt::AddDictionaryWordPrompt() :
    QDialog(nullptr),
    ui(new Ui::AddDictionaryWordPrompt)
{
    ui->setupUi(this);
}

AddDictionaryWordPrompt::~AddDictionaryWordPrompt()
{
    delete ui;
}

QString AddDictionaryWordPrompt::getEnglishWord() const
{
    return englishWord;
}

QString AddDictionaryWordPrompt::getTranslation() const
{
    return translation;
}

void AddDictionaryWordPrompt::on_editEnglishWord_editingFinished()
{
    englishWord = ui->editEnglishWord->text();
}

void AddDictionaryWordPrompt::on_editTranslation_editingFinished()
{
    translation = ui->editTranslation->text();
}
}
