#pragma once

#include <QObject>
#include <memory>

#include "Glossary.h"

namespace glossary::gui::model
{
class GlossaryAdapter : public QObject
{
    Q_OBJECT
public:
    explicit GlossaryAdapter(QObject* parent = nullptr);

    std::string getRandomPolishWord() const;

private:
    std::unique_ptr<glossary::Glossary> glossary;
};
}