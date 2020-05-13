#include "GlossaryAdapter.h"

#include "GlossaryFactory.h"

// TODO: add GuiFactory class
namespace glossary::gui::model
{

GlossaryAdapter::GlossaryAdapter(QObject* parent)
    : QObject(parent), glossary{glossary::GlossaryFactory::createGlossaryFactory()->createGlossary()}
{
}

std::string GlossaryAdapter::getRandomPolishWord() const
{
    if(const auto polishWord = glossary->getRandomPolishWord())
    {
        return *polishWord;
    }
    return {};
}

}
