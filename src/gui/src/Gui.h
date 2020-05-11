#pragma once

#include "view/MainView.h"
#include <memory>

#include <QObject>

class Gui : public QObject
{
    Q_OBJECT
public:
    explicit Gui();

    void show() const;

private:
    void initialize();

    std::unique_ptr<MainView> mainView;

};

