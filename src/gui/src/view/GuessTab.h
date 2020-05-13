#pragma once

#include <QWidget>

namespace Ui
{
class GuessTab;
}

namespace glossary::gui::view
{
class GuessTab : public QWidget
{
    Q_OBJECT

public:
    explicit GuessTab(QWidget* parent = nullptr);
    ~GuessTab();

private:
    Ui::GuessTab* ui;
};
}
