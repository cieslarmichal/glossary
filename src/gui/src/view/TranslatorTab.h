#pragma once

#include <QWidget>
#include <QStringListModel>
#include "boost/optional.hpp"

namespace glossary::gui::view
{
namespace Ui
{
class TranslatorTab;
}

class TranslatorTab : public QWidget
{
    Q_OBJECT

public:
    explicit TranslatorTab(QWidget* parent = nullptr);
    ~TranslatorTab();

    void setAvailableLanguages(const QStringList&);

signals:
    void notifyAboutTextTranslateRequest(const QString& textToTranslate, const QString& sourceLanguage, const QString& targetLanguage) const;
    void notifyAboutAvailableLanguagesRequest() const;

public slots:
    void onTranslationReceived(const QString& translatedText) const;
    void onAvailableLanguagesReceived(const QStringList& availableLanguages);

private slots:
    void on_buttonTranslate_clicked() const;
    void on_buttonSwitchLanguages_clicked();
    void on_boxSourceLanguages_activated(const QString& sourceLanguage);
    void on_boxTargetLanguages_activated(const QString& targetLanguage);

private:
    Ui::TranslatorTab* ui;

    QStringListModel availableLanguages;
    boost::optional<QString> selectedSourceLanguage;
    boost::optional<QString> selectedTargetLanguage;
};
}
