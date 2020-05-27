#pragma once

#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include "DictionaryFormatter.h"
#include "FormattedDictionariesStorage.h"
#include "DictionaryWordAccumulator.h"

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

    void setDictionaries(const Dictionaries&);

signals:
    void notifyAddNewDictionary(const QString& dictionaryName) const;
    void notifyAddDictionaryFromFile(const QString& dictionaryName, const QString& pathToDictionaryWords) const;
    void notifyRemoveDictionary(const QString& dictionaryName) const;
    void notifyUpdateDictionaryTranslationsRequest(const QString& dictionaryName) const;
    void notifyAddWordWithTranslation(const QString& dictionaryName, const QString& englishWord, const QString& translation) const;
    void notifyAddWordWithoutTranslation(const QString& dictionaryName, const QString& englishWord) const;
    void notifyRemoveWord(const QString& dictionaryName, const QString& englishWord) const;
    void notifyUpdateTranslationRequest(const QString& dictionaryName, const QString& englishWord) const;
    void notifyModifyWord(const QString& dictionaryName, const QString& englishWord, const QString& translation) const;

public slots:
    void onDictionaryWordsUpdate(const DictionaryName&, const DictionaryWords&);
    void onDictionariesUpdate(const Dictionaries&);

private slots:
    void on_buttonAddNewDictionary_clicked();
    void on_buttonAddDictionaryFromFile_clicked();
    void on_buttonRemoveDictionary_clicked();
    void on_buttonUpdateTranslations_clicked();
    void on_buttonAddWord_clicked();
    void on_buttonUpdateTranslation_clicked();
    void on_buttonRemoveWord_clicked();
    void on_listOfDictionaries_clicked(const QModelIndex &index);
    void on_listOfDictionaryWords_clicked(const QModelIndex &index);

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
    boost::optional<QString> currentDictionaryName;
    QStringListModel currentDctionaryWords;
    boost::optional<QString> currentEnglishWord;
};
}
