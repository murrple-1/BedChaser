#ifndef EDITFACILITYDIALOG_H
#define EDITFACILITYDIALOG_H

#include <QDialog>

namespace Ui {
    class EditFacilityDialog;
}

#include <QSharedPointer>

class Location;

class EditFacilityDialog : public QDialog
{
    Q_OBJECT
public:
    EditFacilityDialog(const QSharedPointer<Location> &, QWidget *parent = 0);
    ~EditFacilityDialog();
private:
    Ui::EditFacilityDialog *ui;

    QSharedPointer<Location> location;
public slots:
    void updateFacility();
private slots:
    void on_patientlist_clicked();
};

#endif // EDITFACILITYDIALOG_H
