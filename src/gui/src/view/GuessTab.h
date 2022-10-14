#pragma once

#include <QStringListModel>
#include <QWidget>

#include <optional>

#include "WordDescription.h"

namespace glossary::gui::view
{
namespace Ui
{
class GuessTab;
}

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
    void notifyCheckTranslationCorrectnessClicked(const QString& dictionaryName, const QString& polishWord,
                                                  const QString& englishWordInput) const;

public slots:
    void onNextRandomWordReceived(const QString&) const;
    void onWordDescriptionReceived(const WordDescription&) const;
    void onCheckedTranslationVerdictReceived(bool) const;

private slots:
    void on_buttonNextRandomWord_clicked() const;
    void on_listWithDictionaryNames_clicked(const QModelIndex& dictionaryNameIndex);
    void on_buttonCheckWordDescription_clicked();
    void on_buttonCheckTranslationCorrectness_clicked();
    void on_editPolishWord_textChanged(QString);
    void on_editEnglishTranslation_textChanged(QString);

private:
    QStringListModel dictionaryNamesToRandomizeWordFromModel;
    QList<QString> dictionaryNamesToRandomizeWordFrom;
    std::optional<QString> selectedDictionaryName;

    Ui::GuessTab* ui;
};
}
