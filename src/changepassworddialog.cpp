#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"

#include "user.h"
#include "datamanager.h"

ChangePasswordDialog::ChangePasswordDialog(const QSharedPointer<User> &user, QWidget *parent) :
    QDialog(parent), ui(new Ui::ChangePasswordDialog)
{
    ui->setupUi(this);

    this->user = user;

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ChangePasswordDialog::updateUser);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &ChangePasswordDialog::close);

    ui->name->setText(user->getUserName());
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
}

void ChangePasswordDialog::updateUser()
{
    if(ui->passField->text() == user->getPasswordHash())
    {
        user->setPassword(ui->newpassField->text());
        DataManager::sharedInstance().updateUser(*user);
        close();
    }
    else
    {
        // TODO show error
    }
}
