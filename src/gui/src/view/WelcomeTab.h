#pragma once

#include <QLabel>
#include <QWidget>

namespace glossary::gui::view
{
namespace Ui
{
class WelcomeTab;
}

class WelcomeTab : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeTab(QWidget* parent = nullptr);
    ~WelcomeTab();

private:
    Ui::WelcomeTab* ui;
};
}
