#pragma once

#include <QDialog>
#include <QStringListModel>

#include "WordDescription.h"
#include "WordDescriptionFormatter.h"

namespace Ui
{
class WordDescriptionDialog;
}

namespace glossary::gui::view
{
class WordDescriptionDialog : public QDialog
{
    Q_OBJECT

public:
    WordDescriptionDialog(QWidget* parent, const WordDescription&);
    ~WordDescriptionDialog();

private:
    Ui::WordDescriptionDialog* ui;
    WordDescriptionFormatter wordDescriptionFormatter;
    QStringListModel definitions;
    QStringListModel examples;
    QStringListModel synonyms;
};
}
