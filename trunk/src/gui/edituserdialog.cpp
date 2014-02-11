#include "edituserdialog.h"
#include "ui_edituserdialog.h"
#include "../core/datamanager.h"
#include "iostream"

EditUserDialog::EditUserDialog(LHIN::User * const u, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::EditUserDialog),
        user(u)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateUser()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));

    ui->name->setText(QString(user->getUserName().c_str()));

    if(user->getUserType() == LHIN::SYSADMIN)
        ui->typeCombo->setCurrentIndex(0);
    else if(user->getUserType() == LHIN::ADMIN)
        ui->typeCombo->setCurrentIndex(1);
    else
        ui->typeCombo->setCurrentIndex(2);
}

EditUserDialog::~EditUserDialog()
{
    delete ui;
}

void EditUserDialog::updateUser() {

    try {

        if(!ui->passField->text().trimmed().isEmpty())
            user->setPassword(ui->passField->text().toStdString());

        if(ui->typeCombo->currentText() == "Admin")
            user->setUserType(LHIN::ADMIN);
        else if (ui->typeCombo->currentText() == "SysAdmin")
            user->setUserType(LHIN::SYSADMIN);
        else
            user->setUserType(LHIN::STAFF);

        LHIN::DataManager::getDataManager().updateUser(*user);
    }
    catch(LHIN::Exception & e) {
        std::cout << "Message: " << e.getMessage() << "Cause: " << e.getCause();
    }

    close();
}
