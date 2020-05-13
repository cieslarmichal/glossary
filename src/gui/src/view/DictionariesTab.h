#pragma once

#include <QWidget>

namespace Ui
{
class DictionariesTab;
}

namespace glossary::gui::view
{
class DictionariesTab : public QWidget
{
    Q_OBJECT

public:
    explicit DictionariesTab(QWidget* parent = nullptr);
    ~DictionariesTab();

private:
    Ui::DictionariesTab* ui;
};
}
