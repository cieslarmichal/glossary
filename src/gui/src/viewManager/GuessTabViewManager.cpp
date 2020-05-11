#include "GuessTabViewManager.h"


GuessTabViewManager::GuessTabViewManager(QObject *parent,
                                         std::shared_ptr<GuessTab> guessTabInit,
                                         std::shared_ptr<GlossaryAdapter> adapter)
    : QObject(parent), guessTab{std::move(guessTabInit)}, glossaryAdapter{std::move(adapter)}
{

}
