#pragma once

#include <QWidget>

namespace Ui {
class WelcomeTab;
}

class WelcomeTab : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeTab(QWidget *parent = nullptr);
    ~WelcomeTab();

private:
    Ui::WelcomeTab *ui;
};

