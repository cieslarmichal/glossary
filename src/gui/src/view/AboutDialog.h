#pragma once

#include <QDialog>

namespace glossary::gui::view
{
namespace Ui
{
class AboutDialog;
}

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
