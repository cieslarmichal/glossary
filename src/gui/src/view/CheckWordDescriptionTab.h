#pragma once

#include <QWidget>

namespace Ui {
class CheckWordDescriptionTab;
}

class CheckWordDescriptionTab : public QWidget
{
    Q_OBJECT

public:
    explicit CheckWordDescriptionTab(QWidget *parent = nullptr);
    ~CheckWordDescriptionTab();

private:
    Ui::CheckWordDescriptionTab *ui;
};

