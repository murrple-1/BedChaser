#ifndef EDITFACILITYDIALOG_H
#define EDITFACILITYDIALOG_H

#include <QDialog>

namespace Ui {
    class EditFacilityDialog;
}

#include <QSharedPointer>

class Facility;

class EditFacilityDialog : public QDialog
{
    Q_OBJECT
public:
    EditFacilityDialog(const QSharedPointer<Facility> &, QWidget *parent = 0);
    ~EditFacilityDialog();
private:
    Ui::EditFacilityDialog *ui;

    QSharedPointer<Facility> facility;
public slots:
    void updateFacility();
private slots:
    void patientListClicked();
};

#endif // EDITFACILITYDIALOG_H
