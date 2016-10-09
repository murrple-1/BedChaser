#ifndef WAITINGLISTDIALOG_H
#define WAITINGLISTDIALOG_H

#include <QDialog>

namespace Ui {
    class WaitingListDialog;
}

class QListWidgetItem;

class Region;

class WaitingListDialog : public QDialog
{
    Q_OBJECT
public:
    WaitingListDialog(Region *, QWidget *parent = 0);
    ~WaitingListDialog();

    void updateWaitingList();
private:
    Ui::WaitingListDialog *ui;

    Region * reg;
private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem* item);
    void on_addPButton_clicked();
};

#endif // WAITINGLISTDIALOG_H
