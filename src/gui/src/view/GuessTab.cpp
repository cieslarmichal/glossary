#include "GuessTab.h"

#include <QDebug>

#include "fileSystem/GetProjectPath.h"
#include "ui_GuessTab.h"
#include "WordDescriptionDialog.h"

namespace
{
const auto resourceDirectoryPath = common::fileSystem::getProjectPath("glossary") + "src/gui/resources/";
const auto incorrectAnswerIconPath = resourceDirectoryPath + "incorrectAnswer.png";
const auto correctAnswerIconPath = resourceDirectoryPath + "correctAnswer.png";
const auto nextIcon = resourceDirectoryPath + "next.png";
}

namespace glossary::gui::view
{

GuessTab::GuessTab(QWidget* parent) : QWidget(parent), ui(new Ui::GuessTab)
{
    ui->setupUi(this);

    ui->listWithDictionaryNames->setModel(&dictionaryNamesToRandomizeWordFromModel);

    ui->buttonNextRandomWord->setIcon(QIcon(nextIcon.c_str()));

    ui->editEnglishTranslation->setEnabled(false);

    ui->buttonCheckWordDescription->setEnabled(false);

    ui->buttonCheckTranslationCorrectness->setEnabled(false);
}

GuessTab::~GuessTab()
{
    delete ui;
}

void GuessTab::setAvailableDictionaryNames(const QList<QString>& dictionaryNames)
{
    dictionaryNamesToRandomizeWordFrom = dictionaryNames;

    dictionaryNamesToRandomizeWordFromModel.setStringList(dictionaryNamesToRandomizeWordFrom);
}

void GuessTab::onNextRandomWordReceived(const QString& randomPolishWord) const
{
    ui->editPolishWord->setText(randomPolishWord);
}

void GuessTab::onWordDescriptionReceived(const dictionary::WordDescription& wordDescription) const
{
    WordDescriptionDialog wordDescriptionDialog{nullptr, wordDescription};

    wordDescriptionDialog.show();

    wordDescriptionDialog.exec();
}

void GuessTab::onCheckedTranslationVerdictReceived(bool translationCorrect) const
{
    if (translationCorrect)
    {
        auto correctAnswerIcon = QPixmap(correctAnswerIconPath.c_str());

        int width = ui->labelWithCorrectIcon->width();

        int height = ui->labelWithCorrectIcon->height();

        ui->labelWithCorrectIcon->setPixmap(correctAnswerIcon.scaled(width, height, Qt::KeepAspectRatio));

        ui->labelCheckCorrectness->setText("Correct answer!");
    }
    else
    {
        auto incorrectAnswerIcon = QPixmap(incorrectAnswerIconPath.c_str());

        ui->labelWithCorrectIcon->setPixmap(incorrectAnswerIcon);

        ui->labelCheckCorrectness->setText("Incorrect answer");
    }
}

void GuessTab::on_buttonNextRandomWord_clicked() const
{
    ui->editEnglishTranslation->setText("");

    ui->buttonCheckWordDescription->setEnabled(false);

    ui->buttonCheckTranslationCorrectness->setEnabled(false);

    if (selectedDictionaryName)
    {
        emit notifyNextRandomWordFromDictionaryClicked(*selectedDictionaryName);
        return;
    }

    emit notifyNextRandomWordClicked();
}

void GuessTab::on_listWithDictionaryNames_clicked(const QModelIndex& dictionaryNameIndex)
{
    QString dictionaryName = dictionaryNameIndex.data(Qt::DisplayRole).toString();

    selectedDictionaryName = dictionaryName;
}

void GuessTab::on_buttonCheckWordDescription_clicked()
{
    const auto currentlyInsertedEnglishWord = ui->editEnglishTranslation->text();

    if (currentlyInsertedEnglishWord.isEmpty())
    {
        ui->labelWordDescriptionError->setText("Insert english word");
        return;
    }

    ui->labelWordDescriptionError->setText("");

    emit notifyCheckWordDescriptionClicked(currentlyInsertedEnglishWord);
}

void GuessTab::on_buttonCheckTranslationCorrectness_clicked()
{
    const auto currentPolishWord = ui->editPolishWord->text();

    const auto currentlyInsertedEnglishWord = ui->editEnglishTranslation->text();

    auto wordsDictionary = selectedDictionaryName ? *selectedDictionaryName : "";

    emit notifyCheckTranslationCorrectnessClicked(wordsDictionary, currentPolishWord,
                                                  currentlyInsertedEnglishWord.trimmed());

    on_buttonNextRandomWord_clicked();
}

void GuessTab::on_editPolishWord_textChanged(QString)
{
    ui->editEnglishTranslation->setEnabled(true);
}

void GuessTab::on_editEnglishTranslation_textChanged(QString)
{
    ui->buttonCheckWordDescription->setEnabled(true);

    ui->buttonCheckTranslationCorrectness->setEnabled(true);

    ui->labelWordDescriptionError->setText("");
}

}
