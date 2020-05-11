#pragma once

#include <QObject>
#include <memory>

class DictionariesTab;
class GlossaryAdapter;

class DictionariesTabViewManager : public QObject
{
    Q_OBJECT
public:
    DictionariesTabViewManager(QObject *parent, std::shared_ptr<DictionariesTab>, std::shared_ptr<GlossaryAdapter>);

private:
     std::shared_ptr<DictionariesTab> dictionariesTab;
     std::shared_ptr<GlossaryAdapter> glossaryAdapter;
};

