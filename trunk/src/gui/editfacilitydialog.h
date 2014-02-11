#ifndef EDITFACILITYDIALOG_H
#define EDITFACILITYDIALOG_H

#include <QDialog>
#include "../core/location.h"

namespace Ui {
    class EditFacilityDialog;
}

class EditFacilityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditFacilityDialog(LHIN::Location * const, QWidget *parent = 0);
    ~EditFacilityDialog();

public slots:
    void updateFacility();

private:
    Ui::EditFacilityDialog *ui;
    LHIN::Location * location;


private slots:
    void on_patientlist_clicked();
};

#endif // EDITFACILITYDIALOG_H
