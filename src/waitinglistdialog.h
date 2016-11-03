#ifndef WAITINGLISTDIALOG_H
#define WAITINGLISTDIALOG_H

#include <QDialog>

namespace Ui {
    class WaitingListDialog;
}

#include <QSharedPointer>

class QListWidgetItem;

class Region;

class WaitingListDialog : public QDialog
{
    Q_OBJECT
public:
    WaitingListDialog(const QSharedPointer<Region> &, QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    ~WaitingListDialog();
private:
    void updateWaitingList();

    Ui::WaitingListDialog *ui;

    QSharedPointer<Region> region;
private slots:
    void listItemDoubleClicked(QListWidgetItem* item);
    void addPatientButtonClicked();
};

#endif // WAITINGLISTDIALOG_H
