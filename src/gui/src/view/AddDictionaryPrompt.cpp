#include "AddDictionaryPrompt.h"
#include "ui_AddDictionaryPrompt.h"

namespace glossary::gui::view
{
AddDictionaryPrompt::AddDictionaryPrompt() :
    QDialog(nullptr),
    ui(new Ui::AddDictionaryPrompt)
{
    ui->setupUi(this);
}

AddDictionaryPrompt::~AddDictionaryPrompt()
{
    delete ui;
}

QString AddDictionaryPrompt::getDictionaryName() const
{
    return dictionaryName;
}

void AddDictionaryPrompt::on_editDictionaryName_editingFinished()
{
    dictionaryName = ui->editDictionaryName->text();
}
}
