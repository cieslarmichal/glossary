#pragma once

#include <QStringListModel>
#include <QWidget>

#include "boost/optional.hpp"

#include "WordDescription.h"

namespace Ui
{
class GuessTab;
}

namespace glossary::gui::view
{
class GuessTab : public QWidget
{
    Q_OBJECT

public:
    explicit GuessTab(QWidget* parent = nullptr);
    ~GuessTab();

    void setAvailableDictionaryNames(const QList<QString>&);

signals:
    void notifyNextRandomWordClicked() const;
    void notifyNextRandomWordFromDictionaryClicked(const QString& dictionaryName) const;
    void notifyCheckWordDescriptionClicked(const QString& englishWord) const;
    void notifyCheckTranslationCorrectnessClicked(const QString& polishWord,
                                                  const QString& englishWordInput) const;

public slots:
    void onNextRandomWordReceived(const QString&) const;
    void onWordDescriptionReceived(const WordDescription&) const;
    void onCheckedTranslationVerdictReceived(bool) const;

private slots:
    void on_buttonNextRandomWord_clicked() const;
    void on_boxWithDictionaryNames_activated(const QString& dictionaryName);
    void on_buttonCheckWordDescription_clicked();
    void on_buttonCheckTranslationCorrectness_clicked();

private:
    QStringListModel dictionaryNamesToRandomizeWordFromModel;
    QList<QString> dictionaryNamesToRandomizeWordFrom;
    boost::optional<QString> selectedDictionaryName;

    Ui::GuessTab* ui;
};
}
