#include "waitinglistdialog.h"
#include "ui_waitinglistdialog.h"

#include "searchwindow.h"
#include "patient.h"
#include "region.h"
#include "datamanager.h"

WaitingListDialog::WaitingListDialog(const QSharedPointer<Region> &region, QWidget *parent) :
    QDialog(parent), ui(new Ui::WaitingListDialog)
{
    ui->setupUi(this);

    this->region = region;

    updateWaitingList();
}

WaitingListDialog::~WaitingListDialog()
{
    delete ui;
}

void WaitingListDialog::updateWaitingList()
{
    ui->listWidget->clear();

    // TODO foreach patient in region, add to list
}

void WaitingListDialog::on_addPButton_clicked()
{
    SearchWindow sw;
    if(sw.exec() == SearchWindow::Accepted)
    {
        if(!sw.getChosenObject().isNull())
        {

            QSharedPointer<Patient> patient = sw.getChosenObject().dynamicCast<Patient>();
            // TODO add patient to waiting list

            updateWaitingList();
        }
    }
}

void WaitingListDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item)

    // TODO

    updateWaitingList();
}
