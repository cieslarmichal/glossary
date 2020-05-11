#include "TranslatorTabViewManager.h"

TranslatorTabViewManager::TranslatorTabViewManager(QObject *parent,
                                                   std::shared_ptr<TranslatorTab> translatorTabInit,
                                                   std::shared_ptr<GlossaryAdapter> adapter)
    : QObject(parent), translatorTab{std::move(translatorTabInit)}, glossaryAdapter{std::move(adapter)}
{

}
