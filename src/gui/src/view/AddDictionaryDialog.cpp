#include "AddDictionaryDialog.h"

#include "ui_AddDictionaryDialog.h"

namespace glossary::gui::view
{
AddDictionaryDialog::AddDictionaryDialog() : QDialog(nullptr), ui(new Ui::AddDictionaryDialog)
{
    ui->setupUi(this);
}

AddDictionaryDialog::~AddDictionaryDialog()
{
    delete ui;
}

QString AddDictionaryDialog::getDictionaryName() const
{
    return dictionaryName;
}

void AddDictionaryDialog::on_editDictionaryName_editingFinished()
{
    dictionaryName = ui->editDictionaryName->text();
}
}
