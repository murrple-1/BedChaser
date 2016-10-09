#include "adduserdialog.h"
#include "ui_adduserdialog.h"

#include "user.h"
#include "datamanager.h"

const QString staffStr = "Staff";
const QString adminStr = "Administator";
const QString sysAdStr = "SysAdmin";

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddUserDialog::addUser);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &AddUserDialog::close);

    QStringList ls;
    ls.append(staffStr);
    ls.append(adminStr);
    ls.append(sysAdStr);

    ui->typeCombo->addItems(ls);
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::addUser()
{
    User u(ui->nameField->text(), ui->passField->text(), STAFF);
    QString text = ui->typeCombo->currentText();
    if(text == staffStr)
    {
        u.setUserType(STAFF);
    }
    else if(text == adminStr)
    {
        u.setUserType(ADMIN);
    }
    else
    {
        u.setUserType(SYSADMIN);
    }

    DataManager::sharedInstance().addUser(u);
}
