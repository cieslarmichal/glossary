#pragma once

#include <QDialog>

namespace glossary::gui::view
{
namespace Ui {
class AddDictionaryWordPrompt;
}

class AddDictionaryWordPrompt : public QDialog
{
    Q_OBJECT

public:
    AddDictionaryWordPrompt();
    ~AddDictionaryWordPrompt();

    QString getEnglishWord() const;
    QString getTranslation() const;

private slots:
    void on_editEnglishWord_editingFinished();
    void on_editTranslation_editingFinished();

private:
    Ui::AddDictionaryWordPrompt *ui;
    QString englishWord;
    QString translation;
};
}
