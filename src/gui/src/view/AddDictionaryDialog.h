#pragma once

#include <QDialog>

namespace glossary::gui::view
{
namespace Ui
{
class AddDictionaryDialog;
}

class AddDictionaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDictionaryDialog();
    ~AddDictionaryDialog();

    QString getDictionaryName() const;

private slots:
    void on_editDictionaryName_editingFinished();

private:
    Ui::AddDictionaryDialog* ui;
    QString dictionaryName;
};
}
