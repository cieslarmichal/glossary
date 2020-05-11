#include "DictionariesTabViewManager.h"

DictionariesTabViewManager::DictionariesTabViewManager(QObject *parent,
                                                       std::shared_ptr<DictionariesTab> dictionariesTabInit,
                                                       std::shared_ptr<GlossaryAdapter> adapter)
    : QObject(parent), dictionariesTab{std::move(dictionariesTabInit)}, glossaryAdapter{std::move(adapter)}
{

}
