#pragma once

#include <QStringListModel>
#include <QWidget>

#include "WordDescriptionFormatter.h"

namespace glossary::gui::view
{
namespace Ui
{
class CheckWordDescriptionTab;
}

class CheckWordDescriptionTab : public QWidget
{
    Q_OBJECT
public:
    explicit CheckWordDescriptionTab(QWidget* parent = nullptr);
    ~CheckWordDescriptionTab();

signals:
    void notifyCheckWordDescriptionClicked(const QString& englishWord) const;

public slots:
    void onWordDescriptionReceived(const WordDescription&);

private slots:
    void on_buttonCheckWordDescription_clicked() const;
    void on_editEnglishWord_textChanged(QString) const;

private:
    Ui::CheckWordDescriptionTab* ui;
    WordDescriptionFormatter wordDescriptionFormatter;
    QStringListModel definitions;
    QStringListModel examples;
    QStringListModel synonyms;
};
}
