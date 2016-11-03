#include "waitinglistdialog.h"
#include "ui_waitinglistdialog.h"

#include "searchwindow.h"
#include "patient.h"
#include "region.h"
#include "datamanager.h"

WaitingListDialog::WaitingListDialog(const QSharedPointer<Region> &region, QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::WaitingListDialog)
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

void WaitingListDialog::addPatientButtonClicked()
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

void WaitingListDialog::listItemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item)

    // TODO

    updateWaitingList();
}
