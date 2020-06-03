#include "WelcomeTabViewManager.h"

namespace glossary::gui::viewManager
{

WelcomeTabViewManager::WelcomeTabViewManager(QObject *parent, std::shared_ptr<view::WelcomeTab> welcomeTabInit,
                                             std::shared_ptr<model::GlossaryAdapter> glossaryAdapterInit)
    : QObject(parent), welcomeTab{std::move(welcomeTabInit)}, glossaryAdapter{std::move(glossaryAdapterInit)}
{
    connect(welcomeTab.get(), &view::WelcomeTab::notifyAboutUpdateWordsApiKeyLocationRequest, glossaryAdapter.get(),
            &model::GlossaryAdapter::onUpdateWordsApiKeyLocationRequest);
    connect(welcomeTab.get(), &view::WelcomeTab::notifyAboutUpdateTranslateApiKeyLocationRequest, glossaryAdapter.get(),
            &model::GlossaryAdapter::onUpdateTranslateApiKeyLocationRequest);

    connect(glossaryAdapter.get(), &model::GlossaryAdapter::notifyAboutExternalServicesStatus, welcomeTab.get(),
            &view::WelcomeTab::onExternalServicesStatusReceived);

    welcomeTab->setExternalServicesStatus(glossaryAdapter->getStatusOfConnectionToExternalServices());
}

}
