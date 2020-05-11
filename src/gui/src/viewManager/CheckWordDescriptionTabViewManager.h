#pragma once

#include <QObject>
#include <memory>

class CheckWordDescriptionTab;
class GlossaryAdapter;

class CheckWordDescriptionTabViewManager : public QObject
{
    Q_OBJECT
public:
    CheckWordDescriptionTabViewManager(QObject *parent,
                                                std::shared_ptr<CheckWordDescriptionTab>,
                                                std::shared_ptr<GlossaryAdapter>);

private:
     std::shared_ptr<CheckWordDescriptionTab> wordDescriptionTab;
     std::shared_ptr<GlossaryAdapter> glossaryAdapter;
};

