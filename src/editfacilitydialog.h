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
    EditFacilityDialog(const QSharedPointer<Facility> &, QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    ~EditFacilityDialog();
private:
    Ui::EditFacilityDialog *ui;

    QSharedPointer<Facility> facility;
private slots:
    void updateFacility();
    void patientListClicked();
};

#endif // EDITFACILITYDIALOG_H
