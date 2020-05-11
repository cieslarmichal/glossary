#include "GlossaryAdapter.h"
#include "GlossaryFactory.h"

// TODO: add GuiFactory class
GlossaryAdapter::GlossaryAdapter(QObject *parent)
    : QObject(parent), glossary{glossary::GlossaryFactory::createGlossaryFactory()->createGlossary()}
{
}
