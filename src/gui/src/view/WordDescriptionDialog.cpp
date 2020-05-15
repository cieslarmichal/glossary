#include "WordDescriptionDialog.h"

#include "ui_WordDescriptionDialog.h"

namespace
{
QString dialogTitle = {"%1: word description"};
QString definitionLabel = {"Definitions of %1:"};
QString sentenceLabel = {"Example of usage %1 in a sentence:"};

}
namespace glossary::gui::view
{
WordDescriptionDialog::WordDescriptionDialog(QWidget* parent, const WordDescription& wordDescription)
    : QDialog(parent), ui(new Ui::WordDescriptionDialog)
{
    ui->setupUi(this);
    auto formattedWordDescription = wordDescriptionFormatter.formatWordDescription(wordDescription);

    setWindowTitle(dialogTitle.arg(formattedWordDescription.englishWord));
    ui->labelDefinitions->setText(definitionLabel.arg(formattedWordDescription.englishWord));
    ui->labelUsageInSentence->setText(sentenceLabel.arg(formattedWordDescription.englishWord));

    definitions.setStringList(formattedWordDescription.definitions);
    ui->listWithDefinitions->setModel(&definitions);

    sentences.setStringList(formattedWordDescription.sentences);
    ui->listWithSentences->setModel(&sentences);
}

WordDescriptionDialog::~WordDescriptionDialog()
{
    delete ui;
}
}
