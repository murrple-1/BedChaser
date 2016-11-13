#include "edituserdialog.h"
#include "ui_edituserdialog.h"

#include "user.h"
#include "datamanager.h"

EditUserDialog::EditUserDialog(const QSharedPointer<User> &user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserDialog),
    user(user)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditUserDialog::updateUser);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EditUserDialog::close);

    ui->name->setText(user->getUsername());

    if(user->getType() == UserTypeSystemAdmin)
    {
        ui->typeCombo->setCurrentIndex(0);
    }
    else if(user->getType() == UserTypeAdmin)
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
    if(!ui->passField->text().trimmed().isEmpty())
    {
        user->setPassword(ui->passField->text());
    }

    if(ui->typeCombo->currentIndex() == 1)
    {
        user->setType(UserTypeAdmin);
    }
    else if (ui->typeCombo->currentIndex() == 2)
    {
        user->setType(UserTypeSystemAdmin);
    }
    else
    {
        user->setType(UserTypeStaff);
    }

    DataManager::sharedInstance().updateUser(*user);

    close();
}
