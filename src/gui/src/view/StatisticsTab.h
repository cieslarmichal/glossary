#pragma once

#include <QWidget>

namespace Ui
{
class StatisticsTab;
}

namespace glossary::gui::view
{
class StatisticsTab : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsTab(QWidget* parent = nullptr);
    ~StatisticsTab();

private:
    Ui::StatisticsTab* ui;
};
}
