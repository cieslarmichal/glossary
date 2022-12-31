#include "WordDescriptionDialog.h"

#include "ui_WordDescriptionDialog.h"

namespace
{
QString dialogTitle{"%1: word description"};
QString definitionLabel{"Definitions of %1:"};
QString exampleLabel{"Example of usage %1:"};
QString synonymsLabel{"Synonyms of %1:"};

}
namespace glossary::gui::view
{
WordDescriptionDialog::WordDescriptionDialog(QWidget* parent, const dictionary::WordDescription& wordDescription)
    : QDialog(parent), ui(new Ui::WordDescriptionDialog)
{
    ui->setupUi(this);
    auto formattedWordDescription = wordDescriptionFormatter.formatWordDescription(wordDescription);

    setWindowTitle(dialogTitle.arg(formattedWordDescription.englishWord));
    ui->labelDefinitions->setText(definitionLabel.arg(formattedWordDescription.englishWord));
    ui->labelExamples->setText(exampleLabel.arg(formattedWordDescription.englishWord));
    ui->labelSynonyms->setText(synonymsLabel.arg(formattedWordDescription.englishWord));

    definitions.setStringList(formattedWordDescription.definitions);
    ui->listWithDefinitions->setModel(&definitions);

    examples.setStringList(formattedWordDescription.examples);
    ui->listWithExamples->setModel(&examples);

    synonyms.setStringList(formattedWordDescription.synonyms);
    ui->listWithSynonyms->setModel(&synonyms);
}

WordDescriptionDialog::~WordDescriptionDialog()
{
    delete ui;
}
}
