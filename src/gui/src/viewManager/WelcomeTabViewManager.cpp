#include "WelcomeTabViewManager.h"

namespace glossary::gui::viewManager
{

WelcomeTabViewManager::WelcomeTabViewManager(QObject* parent, std::shared_ptr<view::WelcomeTab> welcomeTabInit,
                                             std::shared_ptr<model::GlossaryAdapter> glossaryAdapterInit)
    : QObject(parent), welcomeTab{std::move(welcomeTabInit)}, glossaryAdapter{std::move(glossaryAdapterInit)}
{
}

}
