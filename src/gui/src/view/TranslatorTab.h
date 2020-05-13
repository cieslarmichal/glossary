#pragma once

#include <QWidget>

namespace Ui
{
class TranslatorTab;
}

namespace glossary::gui::view
{
class TranslatorTab : public QWidget
{
    Q_OBJECT

public:
    explicit TranslatorTab(QWidget* parent = nullptr);
    ~TranslatorTab();

private:
    Ui::TranslatorTab* ui;
};
}
