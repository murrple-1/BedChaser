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

    ui->usernameValueLabel->setText(user->getUsername());

    if(user->getType() == UserTypeSystemAdmin)
    {
        ui->typeComboBox->setCurrentIndex(0);
    }
    else if(user->getType() == UserTypeAdmin)
    {
        ui->typeComboBox->setCurrentIndex(1);
    }
    else
    {
        ui->typeComboBox->setCurrentIndex(2);
    }
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}

void EditUserDialog::updateUser()
{
    if(!ui->passwordLineEdit->text().trimmed().isEmpty())
    {
        user->setPassword(ui->passwordLineEdit->text());
    }

    if(ui->typeComboBox->currentIndex() == 1)
    {
        user->setType(UserTypeAdmin);
    }
    else if (ui->typeComboBox->currentIndex() == 2)
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
