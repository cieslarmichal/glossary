#pragma once

#include <QDialog>

namespace glossary::gui::view
{
namespace Ui
{
class AddDictionaryWordDialog;
}

class AddDictionaryWordDialog : public QDialog
{
    Q_OBJECT

public:
    AddDictionaryWordDialog();
    ~AddDictionaryWordDialog();

    QString getEnglishWord() const;
    QString getTranslation() const;

private slots:
    void on_editEnglishWord_editingFinished();
    void on_editTranslation_editingFinished();

private:
    Ui::AddDictionaryWordDialog* ui;
    QString englishWord;
    QString translation;
};
}
