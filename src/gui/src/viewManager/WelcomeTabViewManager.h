#pragma once

#include <QObject>
#include <memory>

#include "model/GlossaryAdapter.h"
#include "view/WelcomeTab.h"

namespace glossary::gui::viewManager
{
class WelcomeTabViewManager : public QObject
{
    Q_OBJECT
public:
    explicit WelcomeTabViewManager(QObject *parent, std::shared_ptr<view::WelcomeTab>, std::shared_ptr<model::GlossaryAdapter>);

private:
    std::shared_ptr<view::WelcomeTab> welcomeTab;
    std::shared_ptr<model::GlossaryAdapter> glossaryAdapter;
};
}
