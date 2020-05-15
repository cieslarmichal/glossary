#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <memory>

#include "Glossary.h"

namespace glossary::gui::model
{
class GlossaryAdapter : public QObject
{
    Q_OBJECT
public:
    explicit GlossaryAdapter(QObject* parent = nullptr);

    QString getRandomPolishWord() const;
    QString getRandomPolishWord(const QString& dictionaryName) const;
    WordDescription getWordDescription(const QString& englishWord) const;
    bool verifyCorrectnessOfTranslation(const QString& polishWord, const QString& englishWord) const;
    QList<QString> getDictionaryNames() const;

signals:
    void notifyAboutRandomPolishWord(const QString&) const;
    void notifyAboutWordDescription(const WordDescription&) const;
    void notifyAboutTranslationVerdict(bool) const;

public slots:
    void onRandomPolishWordTriggered() const;
    void onRandomPolishWordFromDictionaryTriggered(const QString& dictionaryName) const;
    void onWordDescriptionTriggered(const QString& englishWord) const;
    void onTranslationCorectnessTriggered(const QString& polishWord, const QString& englishWord) const;

private:
    std::unique_ptr<glossary::Glossary> glossary;
};
}
