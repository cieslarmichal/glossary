#include "CheckWordDescriptionTabViewManager.h"

#include <utility>

CheckWordDescriptionTabViewManager::CheckWordDescriptionTabViewManager(QObject *parent,
                                                                       std::shared_ptr<CheckWordDescriptionTab> wordDescriptionTabInit,
                                                                       std::shared_ptr<GlossaryAdapter> adapter)
    : QObject(parent), wordDescriptionTab{std::move(wordDescriptionTabInit)}, glossaryAdapter{std::move(adapter)}
{

}
