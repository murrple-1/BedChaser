#include "edituserdialog.h"
#include "ui_edituserdialog.h"

#include "user.h"
#include "datamanager.h"
#include "exception.h"

EditUserDialog::EditUserDialog(User *u, QWidget *parent) :
    QDialog(parent), ui(new Ui::EditUserDialog), user(u)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditUserDialog::updateUser);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EditUserDialog::close);

    ui->name->setText(user->getUserName());

    if(user->getUserType() == SYSADMIN)
    {
        ui->typeCombo->setCurrentIndex(0);
    }
    else if(user->getUserType() == ADMIN)
    {
        ui->typeCombo->setCurrentIndex(1);
    }
    else
    {
        ui->typeCombo->setCurrentIndex(2);
    }
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}

void EditUserDialog::updateUser()
{
    try {
        if(!ui->passField->text().trimmed().isEmpty())
        {
            user->setPassword(ui->passField->text());
        }

        if(ui->typeCombo->currentText() == "Admin")
        {
            user->setUserType(ADMIN);
        }
        else if (ui->typeCombo->currentText() == "SysAdmin")
        {
            user->setUserType(SYSADMIN);
        }
        else
        {
            user->setUserType(STAFF);
        }

        DataManager::sharedInstance().updateUser(*user);
    }
    catch(Exception & e)
    {
        // TODO
    }

    close();
}
