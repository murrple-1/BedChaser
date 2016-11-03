#include "adduserdialog.h"
#include "ui_adduserdialog.h"

#include "user.h"
#include "datamanager.h"

static const QString StaffString = "Staff";
static const QString AdminString = "Administator";
static const QString SystemAdminString = "SysAdmin";

AddUserDialog::AddUserDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddUserDialog::addUser);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &AddUserDialog::close);

    QStringList ls;
    ls.append(StaffString);
    ls.append(AdminString);
    ls.append(SystemAdminString);

    ui->typeCombo->addItems(ls);
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::addUser()
{
    UserType userType;
    QString text = ui->typeCombo->currentText();
    if(text == AdminString)
    {
        userType = UserTypeAdmin;
    }
    else if(text == SystemAdminString)
    {
        userType = UserTypeSystemAdmin;
    }
    else
    {
        userType = UserTypeStaff;
    }

    User u(QVariant(), ui->nameField->text(), ui->passField->text(), userType);
    DataManager::sharedInstance().addUser(u);
}
