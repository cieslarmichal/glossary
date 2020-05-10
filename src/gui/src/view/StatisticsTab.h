#pragma once

#include <QWidget>

namespace Ui {
class StatisticsTab;
}

class StatisticsTab : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsTab(QWidget *parent = nullptr);
    ~StatisticsTab();

private:
    Ui::StatisticsTab *ui;
};

