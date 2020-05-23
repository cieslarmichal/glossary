#pragma once

#include <QWidget>

namespace glossary::gui::view
{

namespace Ui
{
class DictionariesTab;
}

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
