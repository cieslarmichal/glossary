#pragma once

#include <QWidget>


namespace glossary::gui::view
{
namespace Ui
{
class TranslatorTab;
}

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
