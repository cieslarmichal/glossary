#pragma once
#include <QObject>
#include <memory>

class GuessTab;
class GlossaryAdapter;

class GuessTabViewManager : public QObject
{
    Q_OBJECT
public:
    GuessTabViewManager(QObject *parent, std::shared_ptr<GuessTab>, std::shared_ptr<GlossaryAdapter>);

private:
     std::shared_ptr<GuessTab> guessTab;
     std::shared_ptr<GlossaryAdapter> glossaryAdapter;
};

