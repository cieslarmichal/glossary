#include "TranslatorTab.h"

#include "fileSystem/GetProjectPath.h"
#include "ui_TranslatorTab.h"

namespace glossary::gui::view
{

namespace
{
const auto resourceDirectoryPath = common::fileSystem::getProjectPath("glossary") + "src/gui/resources/";
const auto switchLanguagesIconPath = resourceDirectoryPath + "swap.png";
}

TranslatorTab::TranslatorTab(QWidget* parent) : QWidget(parent), ui(new Ui::TranslatorTab)
{
    ui->setupUi(this);
    ui->buttonSwitchLanguages->setIcon(QIcon(switchLanguagesIconPath.c_str()));
    ui->boxSourceLanguages->setModel(&availableLanguages);
    ui->boxTargetLanguages->setModel(&availableLanguages);
    ui->buttonSwitchLanguages->setEnabled(false);
    ui->buttonTranslate->setEnabled(false);
}

TranslatorTab::~TranslatorTab()
{
    delete ui;
}

void TranslatorTab::setAvailableLanguages(const QStringList& availableLanguagesInit)
{
    availableLanguages.setStringList(availableLanguagesInit);
}

void TranslatorTab::onTranslationReceived(const QString& translation) const
{
    ui->editTranslatedText->setText(translation.toLower());
}

void TranslatorTab::onAvailableLanguagesReceived(const QStringList& availableLanguagesInput)
{
    setAvailableLanguages(availableLanguagesInput);
}

void TranslatorTab::on_buttonTranslate_clicked() const
{
    auto insertedText = ui->editTextToTranslate->text();
    if (not insertedText.isEmpty() && selectedSourceLanguage && selectedTargetLanguage)
    {
        emit notifyAboutTextTranslateRequest(insertedText, *selectedSourceLanguage, *selectedTargetLanguage);
    }
}

void TranslatorTab::on_buttonSwitchLanguages_clicked()
{
    if (selectedSourceLanguage && selectedTargetLanguage)
    {
        if (const int sourceLanguageIndex = ui->boxSourceLanguages->findText(*selectedTargetLanguage);
            sourceLanguageIndex != -1)
        {
            ui->boxSourceLanguages->setCurrentIndex(sourceLanguageIndex);
        }

        if (const int targetLanguageIndex = ui->boxTargetLanguages->findText(*selectedSourceLanguage);
            targetLanguageIndex != -1)
        {
            ui->boxTargetLanguages->setCurrentIndex(targetLanguageIndex);
        }

        auto tempSourcelanguage = *selectedSourceLanguage;
        selectedSourceLanguage = *selectedTargetLanguage;
        selectedTargetLanguage = tempSourcelanguage;

        auto tempTextToTranslate = ui->editTextToTranslate->text();
        ui->editTextToTranslate->setText(ui->editTranslatedText->text());
        ui->editTranslatedText->setText(tempTextToTranslate);
    }
}

void TranslatorTab::on_boxSourceLanguages_activated(const QString& sourceLanguage)
{
    selectedSourceLanguage = sourceLanguage;
    if (selectedSourceLanguage && selectedTargetLanguage)
    {
        ui->buttonSwitchLanguages->setEnabled(true);
        ui->buttonTranslate->setEnabled(true);
    }
}

void TranslatorTab::on_boxTargetLanguages_activated(const QString& targetLanguage)
{
    selectedTargetLanguage = targetLanguage;
    if (selectedSourceLanguage && selectedTargetLanguage)
    {
        ui->buttonSwitchLanguages->setEnabled(true);
        ui->buttonTranslate->setEnabled(true);
    }
}

}
