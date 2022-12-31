#pragma once

#include <QStringList>
#include <QStringListModel>
#include <QWidget>

#include "dictionary/Dictionary.h"
#include "DictionaryFormatter.h"
#include "DictionaryWordAccumulator.h"
#include "FormattedDictionariesStorage.h"

namespace glossary::gui::view
{
namespace Ui
{
class DictionariesTab;
}

class DictionariesTab : public QWidget
{
    Q_OBJECT
public:
    explicit DictionariesTab(QWidget* parent = nullptr);
    ~DictionariesTab();

    void setDictionaries(const std::vector<dictionary::Dictionary>&);

signals:
    void notifyAddNewDictionary(const QString& dictionaryName) const;
    void notifyAddDictionaryFromFile(const QString& dictionaryName, const QString& pathToDictionaryWords) const;
    void notifyRemoveDictionary(const QString& dictionaryName) const;
    void notifyUpdateDictionaryTranslationsRequest(const QString& dictionaryName) const;
    void notifyAddWordWithTranslation(const QString& dictionaryName, const QString& englishWord,
                                      const QString& translation) const;
    void notifyAddWordWithoutTranslation(const QString& dictionaryName, const QString& englishWord) const;
    void notifyRemoveWord(const QString& dictionaryName, const QString& englishWord) const;
    void notifyUpdateTranslationRequest(const QString& dictionaryName, const QString& englishWord) const;
    void notifyModifyWord(const QString& dictionaryName, const QString& englishWord, const QString& translation) const;

public slots:
    void onDictionaryWordsUpdate(const std::string&, const std::vector<dictionary::DictionaryWord>&);
    void onDictionariesUpdate(const std::vector<dictionary::Dictionary>&);

private slots:
    void on_buttonAddNewDictionary_clicked();
    void on_buttonAddDictionaryFromFile_clicked();
    void on_buttonRemoveDictionary_clicked();
    void on_buttonUpdateTranslations_clicked();
    void on_buttonAddWord_clicked();
    void on_buttonUpdateTranslation_clicked();
    void on_buttonRemoveWord_clicked();
    void on_listOfDictionaries_clicked(const QModelIndex& index);
    void on_listOfDictionaryWords_clicked(const QModelIndex& index);

private:
    void synchronizeDictionariesModel();
    void synchronizeDictionaryWordsModel(const QString& dictionaryName);
    void clearDictionaryWordsModel();
    void setDictionaryWordsNoFocusButtonsEnabled(bool enabled);
    void setDictionaryWordsWithFocusButtonsEnabled(bool enabled);
    void setDictionaryButtonsEnabled(bool enabled);

    Ui::DictionariesTab* ui;
    DictionaryFormatter dictionaryFormatter;
    DictionaryWordAccumulator dictionaryWordAccumulator;

    FormattedDictionariesStorage dictionariesStorage;
    QStringListModel dictionaryNames;
    std::optional<QString> currentDictionaryName;
    QStringListModel currentDctionaryWords;
    std::optional<QString> currentEnglishWord;
};
}
