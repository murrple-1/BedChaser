#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include "../core/datamanager.h"
#include "qerrormessage.h"

const QString staffStr = "Staff";
const QString adminStr = "Administator";
const QString sysAdStr = "SysAdmin";

AddUserDialog::AddUserDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(addUser()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));

    QStringList ls;
    ls.push_back(staffStr);
    ls.push_back(adminStr);
    ls.push_back(sysAdStr);

    ui->typeCombo->addItems(ls);
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::addUser() {
    LHIN::User u(ui->nameField->text().toStdString(), ui->passField->text().toStdString(), LHIN::STAFF);
    QString text = ui->typeCombo->currentText();
    if(text == staffStr)
    {
        u.setUserType(LHIN::STAFF);
    } else if(text == adminStr)
    {
        u.setUserType(LHIN::ADMIN);
    } else
    {
        u.setUserType(LHIN::SYSADMIN);
    }
    try {
        LHIN::DataManager::getDataManager().addUser(u);
    }
    catch(LHIN::Exception & e) {
        QErrorMessage error(this);
        error.showMessage("The user is already created");
        error.exec();
    }
}
