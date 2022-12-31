#include "WelcomeTab.h"

#include <iostream>
#include <QDir>
#include <QFileDialog>

#include "fileSystem/GetProjectPath.h"
#include "ui_WelcomeTab.h"

namespace
{
const auto resourceDirectoryPath = common::fileSystem::getProjectPath("glossary") + "src/gui/resources/";
const auto loadApiKeyIconPath = resourceDirectoryPath + "settings.png";
}

namespace glossary::gui::view
{
WelcomeTab::WelcomeTab(QWidget* parent) : QWidget(parent), ui(new Ui::WelcomeTab)
{
    ui->setupUi(this);
    ui->buttonLoadWordsApiKey->setIcon(QIcon(loadApiKeyIconPath.c_str()));
    ui->buttonLoadTranslateApiKey->setIcon(QIcon(loadApiKeyIconPath.c_str()));
}

WelcomeTab::~WelcomeTab()
{
    delete ui;
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
