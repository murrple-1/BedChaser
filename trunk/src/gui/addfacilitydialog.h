#ifndef ADDFACILITYDIALOG_H
#define ADDFACILITYDIALOG_H

#include <QDialog>

namespace Ui {
    class AddFacilityDialog;
}

class AddFacilityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFacilityDialog(QWidget *parent = 0);
    ~AddFacilityDialog();

public slots:
    void addFacility();

private:
    Ui::AddFacilityDialog *ui;
};

#endif // ADDFACILITYDIALOG_H
