#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"
#include "../core/datamanager.h"
#include <QErrorMessage>

ChangePasswordDialog::ChangePasswordDialog(LHIN::User * const u, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ChangePasswordDialog),
        user(u)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateUser()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));

    ui->name->setText(QString(user->getUserName().c_str()));
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
}

void ChangePasswordDialog::updateUser() {
    if(ui->passField->text().toStdString() == user->getPassword()) {
        user->setPassword(ui->newpassField->text().toStdString());
        LHIN::DataManager::getDataManager().updateUser(*user);
        close();
    }
    else {
        QErrorMessage error(this);
        error.showMessage("Your password did not match");
        error.exec();
    }
}
