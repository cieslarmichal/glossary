#pragma once

#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include "DictionaryFormatter.h"
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

    void setDictionaries(const Dictionaries&);

signals:
    void notifyAddNewDictionary(const QString& dictionaryName) const;
    void notifyAddDictionaryFromFile(const QString& dictionaryName, const QString& pathToDictionaryWords) const;
    void notifyRemoveDictionary(const QString& dictionaryName) const;
    void notifyUpdateDictionaryTranslationsRequest(const QString& dictionaryName) const;
    void notifyAddWord(const QString& dictionaryName, const QString& englishWord, const QString& translation) const;
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
    void on_buttonModifyWord_clicked();
    void on_buttonUpdateTranslation_clicked();
    void on_buttonRemoveWord_clicked();

private:
    void synchronizeDictionariesModels();

    Ui::DictionariesTab* ui;
    DictionaryFormatter dictionaryFormatter;
    FormattedDictionariesStorage currentDictionaries;
    QStringListModel currentDictionaryNames;
    QStringListModel currentDictionaryWords;
    QStringListModel currentDictionaryTranslations;
};
}
