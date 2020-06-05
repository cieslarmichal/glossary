#include "WelcomeTab.h"

#include <QDir>
#include <QFileDialog>
#include <iostream>

#include "ui_WelcomeTab.h"
#include "utils/GetProjectPath.h"

namespace
{
const auto resourceDirectoryPath = utils::getProjectPath("glossary") + "src/gui/resources/";
const auto loadApiKeyIconPath = resourceDirectoryPath + "settings.png";
const auto validApiKeyIconPath = resourceDirectoryPath + "correctAnswer.png";
const auto invalidApiKeyIconPath = resourceDirectoryPath + "incorrectAnswer.png";
}

namespace glossary::gui::view
{
WelcomeTab::WelcomeTab(QWidget* parent) : QWidget(parent), ui(new Ui::WelcomeTab)
{
    ui->setupUi(this);
    ui->buttonLoadWordsApiKey->setIcon(QIcon(loadApiKeyIconPath.c_str()));
    ui->buttonLoadTranslateApiKey->setIcon(QIcon(loadApiKeyIconPath.c_str()));
    setInvalidApiKeyIcon(ui->labelTranslateApiKeyValid);
    setInvalidApiKeyIcon(ui->labelWordsApiKeyValid);
}

WelcomeTab::~WelcomeTab()
{
    delete ui;
}

void WelcomeTab::setExternalServicesStatus(const ExternalServicesStatus& externalServicesStatus)
{
    onExternalServicesStatusReceived(externalServicesStatus);
}

void WelcomeTab::onExternalServicesStatusReceived(const ExternalServicesStatus& externalServicesStatus)
{
    if (wordsApiValid(externalServicesStatus.wordsApiStatus))
    {
        setValidApiKeyIcon(ui->labelWordsApiKeyValid);
        setWordsApiRelatedTabsEnabled(true);
    }
    else
    {
        setInvalidApiKeyIcon(ui->labelWordsApiKeyValid);
        setWordsApiRelatedTabsEnabled(false);
    }

    if (translationApiValid(externalServicesStatus.translationApiStatus))
    {
        setValidApiKeyIcon(ui->labelTranslateApiKeyValid);
        setTranslateApiRelatedTabsEnabled(true);
    }
    else
    {
        setInvalidApiKeyIcon(ui->labelTranslateApiKeyValid);
        setTranslateApiRelatedTabsEnabled(false);
    }
}

void WelcomeTab::on_buttonLoadTranslateApiKey_clicked()
{
    auto pathToFileWithTranslateApiKey =
        QFileDialog::getOpenFileName(this, "Open file with translate api key");
    emit notifyAboutUpdateTranslateApiKeyLocationRequest(pathToFileWithTranslateApiKey);
}

void WelcomeTab::on_buttonLoadWordsApiKey_clicked()
{
    auto pathToFileWithWordsApiKey = QFileDialog::getOpenFileName(this, "Open file with words api key");
    emit notifyAboutUpdateWordsApiKeyLocationRequest(pathToFileWithWordsApiKey);
}

bool WelcomeTab::wordsApiValid(WordsApiStatus wordsApiStatus) const
{
    return wordsApiStatus == WordsApiStatus::Available;
}

bool WelcomeTab::translationApiValid(TranslationApiStatus translationApiStatus) const
{
    return translationApiStatus == TranslationApiStatus::Available;
}

void WelcomeTab::setValidApiKeyIcon(QLabel* label)
{
    auto validTranslateApiKeyIcon = QPixmap(validApiKeyIconPath.c_str());
    int width = label->width();
    int height = label->height();
    label->setPixmap(validTranslateApiKeyIcon.scaled(width, height, Qt::KeepAspectRatio));
}

void WelcomeTab::setInvalidApiKeyIcon(QLabel* label)
{
    auto invalidTranslateApiKeyIcon = QPixmap(invalidApiKeyIconPath.c_str());
    int width = label->width();
    int height = label->height();
    label->setPixmap(invalidTranslateApiKeyIcon.scaled(width, height, Qt::KeepAspectRatio));
}

void WelcomeTab::setWordsApiRelatedTabsEnabled(bool tabsEnabled) const
{
    emit notifyAboutSetGuessTabEnabledRequest(tabsEnabled);
    emit notifyAboutSetDictionariesTabEnabledRequest(tabsEnabled);
    emit notifyAboutSetWordDescriptionTabEnabledRequest(tabsEnabled);
}

void WelcomeTab::setTranslateApiRelatedTabsEnabled(bool tabsEnabled) const
{
    emit notifyAboutSetTranslatorTabEnabledRequest(tabsEnabled);
}

}
