#pragma once

#include <QObject>
#include "Glossary.h"
#include <memory>

class GlossaryAdapter : public QObject
{
    Q_OBJECT
public:
    explicit GlossaryAdapter(QObject *parent = nullptr);

private:
    std::unique_ptr<glossary::Glossary> glossary;

};

