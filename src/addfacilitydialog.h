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
    AddFacilityDialog(QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    ~AddFacilityDialog();
private:
    Ui::AddFacilityDialog *ui;
private slots:
    void addFacility();
};

#endif // ADDFACILITYDIALOG_H
