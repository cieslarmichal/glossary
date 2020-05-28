#include "CheckWordDescriptionTab.h"

#include "ui_CheckWordDescriptionTab.h"
#include <QShortcut>

namespace glossary::gui::view
{
CheckWordDescriptionTab::CheckWordDescriptionTab(QWidget* parent)
    : QWidget(parent), ui(new Ui::CheckWordDescriptionTab)
{
    ui->setupUi(this);
    ui->listWithDefinitions->setModel(&definitions);
    ui->listWithExamples->setModel(&examples);
    ui->listWithSynonyms->setModel(&synonyms);
    ui->buttonCheckWordDescription->setEnabled(false);
}

CheckWordDescriptionTab::~CheckWordDescriptionTab()
{
    delete ui;
}

void CheckWordDescriptionTab::onWordDescriptionReceived(const WordDescription& wordDescription)
{
    auto formattedWordDescription = wordDescriptionFormatter.formatWordDescription(wordDescription);

    if (formattedWordDescription.isEmpty())
    {
        ui->labelWordDescriptionError->setText("Invalid english word");
        return;
    }

    definitions.setStringList(formattedWordDescription.definitions);
    examples.setStringList(formattedWordDescription.examples);
    synonyms.setStringList(formattedWordDescription.synonyms);
    ui->labelWordDescriptionError->setText("");
}

void CheckWordDescriptionTab::on_buttonCheckWordDescription_clicked() const
{
    const auto currentlyInsertedEnglishWord = ui->editEnglishWord->text();
    if (currentlyInsertedEnglishWord.toStdString().empty())
    {
        ui->labelWordDescriptionError->setText("Insert english word");
        return;
    }
    ui->labelWordDescriptionError->setText("");
    emit notifyCheckWordDescriptionClicked(currentlyInsertedEnglishWord);
}

void CheckWordDescriptionTab::on_editEnglishWord_textChanged(QString) const
{
    ui->buttonCheckWordDescription->setEnabled(true);
}
}
