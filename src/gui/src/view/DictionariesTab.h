#pragma once

#include <QWidget>

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

private slots:
    void on_buttonAddNewDictionary_clicked();
    void on_buttonAddDictionaryFromFile_clicked();
    void on_butonRemoveDictionary_clicked();
    void on_buttonUpdateTranslations_clicked();
    void on_buttonAddWord_clicked();
    void on_buttonModifyWord_clicked();
    void on_buttonUpdateTranslation_clicked();
    void on_buttonRemoveWord_clicked();

private:
    Ui::DictionariesTab* ui;
    
};
}
