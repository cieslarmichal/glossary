#include "DictionariesTabViewManager.h"

namespace glossary::gui::viewManager
{

using namespace view;
using namespace model;

DictionariesTabViewManager::DictionariesTabViewManager(
    QObject* parent, std::shared_ptr<view::DictionariesTab> dictionariesTabInit,
    std::shared_ptr<model::GlossaryAdapter> adapter)
    : QObject(parent), dictionariesTab{std::move(dictionariesTabInit)}, glossaryAdapter{std::move(adapter)}
{
    connect(dictionariesTab.get(), &DictionariesTab::notifyAddNewDictionary, glossaryAdapter.get(),
            &GlossaryAdapter::onDictionaryAdded);
    connect(dictionariesTab.get(), &DictionariesTab::notifyAddDictionaryFromFile, glossaryAdapter.get(),
            &GlossaryAdapter::onDictionaryAddedFromFile);
    connect(dictionariesTab.get(), &DictionariesTab::notifyRemoveDictionary, glossaryAdapter.get(),
            &GlossaryAdapter::onDictionaryRemoved);
    connect(dictionariesTab.get(), &DictionariesTab::notifyUpdateDictionaryTranslationsRequest, glossaryAdapter.get(),
            &GlossaryAdapter::onDictionaryTranslationsUpdateRequest);
    connect(dictionariesTab.get(), &DictionariesTab::notifyAddWordWithTranslation, glossaryAdapter.get(),
            &GlossaryAdapter::onWordWithTranslationAdded);
    connect(dictionariesTab.get(), &DictionariesTab::notifyAddWordWithoutTranslation, glossaryAdapter.get(),
            &GlossaryAdapter::onWordWithoutTranslationAdded);
    connect(dictionariesTab.get(), &DictionariesTab::notifyRemoveWord, glossaryAdapter.get(),
            &GlossaryAdapter::onWordRemoved);
    connect(dictionariesTab.get(), &DictionariesTab::notifyModifyWord, glossaryAdapter.get(),
            &GlossaryAdapter::onWordTranslationChanged);
    connect(dictionariesTab.get(), &DictionariesTab::notifyUpdateTranslationRequest, glossaryAdapter.get(),
            &GlossaryAdapter::onWordTranslationUpdateRequest);

    connect(glossaryAdapter.get(), &GlossaryAdapter::notifyAboutDictionariesUpdate, dictionariesTab.get(),
            &DictionariesTab::onDictionariesUpdate);
    connect(glossaryAdapter.get(), &GlossaryAdapter::notifyAboutDictionaryWordsUpdate, dictionariesTab.get(),
            &DictionariesTab::onDictionaryWordsUpdate);

    dictionariesTab->setDictionaries(glossaryAdapter->getDictionaries());
}
}
