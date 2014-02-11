#ifndef WAITINGLISTDIALOG_H
#define WAITINGLISTDIALOG_H

#include <QDialog>
#include "../core/region.h"
#include "QListWidgetItem"

namespace Ui {
    class WaitingListDialog;
}

class WaitingListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingListDialog(LHIN::Region * const, QWidget *parent = 0);
    void updateWaitingList();
    ~WaitingListDialog();

private:
    Ui::WaitingListDialog *ui;
    LHIN::Region * reg;

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem* item);
    void on_addPButton_clicked();
};

#endif // WAITINGLISTDIALOG_H
