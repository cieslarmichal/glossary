#pragma once

#include <QWidget>
#include <QLabel>
#include "ExternalServicesStatus.h"

namespace glossary::gui::view
{
namespace Ui {
class WelcomeTab;
}

class WelcomeTab : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeTab(QWidget *parent = nullptr);
    ~WelcomeTab();

    void setExternalServicesStatus(const ExternalServicesStatus&);

signals:
    void notifyAboutUpdateTranslateApiKeyLocationRequest(const QString& translateApiKeyLocation) const;
    void notifyAboutUpdateWordsApiKeyLocationRequest(const QString& wordsApiKeyLocation) const;

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

    Ui::WelcomeTab *ui;
};
}
