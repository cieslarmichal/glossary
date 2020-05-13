#pragma once

#include <QObject>
#include <memory>
#include "model/GlossaryAdapter.h"
#include "view/DictionariesTab.h"

namespace glossary::gui::viewManager
{
class DictionariesTabViewManager : public QObject
{
    Q_OBJECT
public:
    DictionariesTabViewManager(QObject* parent, std::shared_ptr<view::DictionariesTab>,
                               std::shared_ptr<model::GlossaryAdapter>);

private:
    std::shared_ptr<view::DictionariesTab> dictionariesTab;
    std::shared_ptr<model::GlossaryAdapter> glossaryAdapter;
};
}
