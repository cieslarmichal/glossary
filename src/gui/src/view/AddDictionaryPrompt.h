#pragma once

#include <QDialog>

namespace glossary::gui::view
{
namespace Ui {
class AddDictionaryPrompt;
}

class AddDictionaryPrompt : public QDialog
{
    Q_OBJECT

public:
    explicit AddDictionaryPrompt();
    ~AddDictionaryPrompt();

    QString getDictionaryName() const;

private slots:
    void on_editDictionaryName_editingFinished();

private:
    Ui::AddDictionaryPrompt *ui;
    QString dictionaryName;
};
}
