#pragma once

#include <QDialog>

namespace Ui
{
class AboutDialog;
}

namespace glossary::gui::view
{
class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget* parent = nullptr);
    ~AboutDialog();

private:
    Ui::AboutDialog* ui;
};
}
