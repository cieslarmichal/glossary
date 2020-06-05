#pragma once

#include <QLabel>
#include <QWidget>

#include "ExternalServicesStatus.h"

namespace glossary::gui::view
{
namespace Ui
{
class WelcomeTab;
}

class WelcomeTab : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeTab(QWidget* parent = nullptr);
    ~WelcomeTab();

    void setExternalServicesStatus(const ExternalServicesStatus&);

signals:
    void notifyAboutUpdateTranslateApiKeyLocationRequest(const QString& translateApiKeyLocation) const;
    void notifyAboutUpdateWordsApiKeyLocationRequest(const QString& wordsApiKeyLocation) const;
    void notifyAboutSetGuessTabEnabledRequest(bool tabEnabled) const;
    void notifyAboutSetDictionariesTabEnabledRequest(bool tabEnabled) const;
    void notifyAboutSetWordDescriptionTabEnabledRequest(bool tabEnabled) const;
    void notifyAboutSetTranslatorTabEnabledRequest(bool tabEnabled) const;

public slots:
    void onExternalServicesStatusReceived(const ExternalServicesStatus&);

private slots:
    void on_buttonLoadTranslateApiKey_clicked();
    void on_buttonLoadWordsApiKey_clicked();

private:
    bool wordsApiValid(WordsApiStatus) const;
    bool translationApiValid(TranslationApiStatus) const;
    void setValidApiKeyIcon(QLabel*);
    void setInvalidApiKeyIcon(QLabel*);
    void setWordsApiRelatedTabsEnabled(bool tabsEnabled) const;
    void setTranslateApiRelatedTabsEnabled(bool tabsEnabled) const;

    Ui::WelcomeTab* ui;
};
}
