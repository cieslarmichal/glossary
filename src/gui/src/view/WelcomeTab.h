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

signals:
    void notifyAboutSetGuessTabEnabledRequest(bool tabEnabled) const;
    void notifyAboutSetDictionariesTabEnabledRequest(bool tabEnabled) const;
    void notifyAboutSetWordDescriptionTabEnabledRequest(bool tabEnabled) const;
    void notifyAboutSetTranslatorTabEnabledRequest(bool tabEnabled) const;

private:
    void setWordsApiRelatedTabsEnabled(bool tabsEnabled) const;
    void setTranslateApiRelatedTabsEnabled(bool tabsEnabled) const;

    Ui::WelcomeTab* ui;
};
}
