#pragma once

#include <QObject>
#include <memory>
#include "model/GlossaryAdapter.h"
#include "view/TranslatorTab.h"

namespace glossary::gui::viewManager
{
class TranslatorTabViewManager : public QObject
{
    Q_OBJECT
public:
    TranslatorTabViewManager(QObject* parent, std::shared_ptr<view::TranslatorTab>,
                             std::shared_ptr<model::GlossaryAdapter>);

private:
    std::shared_ptr<view::TranslatorTab> translatorTab;
    std::shared_ptr<model::GlossaryAdapter> glossaryAdapter;
};
}
