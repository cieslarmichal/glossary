#pragma once

#include <QObject>
#include <memory>

class TranslatorTab;
class GlossaryAdapter;

class TranslatorTabViewManager : public QObject
{
    Q_OBJECT
public:
    TranslatorTabViewManager(QObject *parent, std::shared_ptr<TranslatorTab>, std::shared_ptr<GlossaryAdapter>);

private:
     std::shared_ptr<TranslatorTab> translatorTab;
     std::shared_ptr<GlossaryAdapter> glossaryAdapter;
};

