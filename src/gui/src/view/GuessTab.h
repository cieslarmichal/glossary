#pragma once

#include <QWidget>

namespace Ui {
class GuessTab;
}

class GuessTab : public QWidget
{
    Q_OBJECT

public:
    explicit GuessTab(QWidget *parent = nullptr);
    ~GuessTab();

private:
    Ui::GuessTab *ui;
};

