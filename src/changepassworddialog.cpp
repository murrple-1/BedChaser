#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"

#include "user.h"
#include "datamanager.h"
#include "passwordhasher.h"

static const QString errorLabelStylesheet = "QLabel { color : red; }";

static const int minPasswordLength = 6;
static const int maxPasswordLength = 128;

ChangePasswordDialog::ChangePasswordDialog(const QSharedPointer<User> &user, QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::ChangePasswordDialog)
{
    ui->setupUi(this);

    this->user = user;

    ui->oldPasswordErrorLabel->setStyleSheet(errorLabelStylesheet);
    ui->newPasswordErrorLabel->setStyleSheet(errorLabelStylesheet);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ChangePasswordDialog::updateUser);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &ChangePasswordDialog::close);

    ui->usernameValueLabel->setText(user->getUsername());
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
}

void ChangePasswordDialog::updateUser()
{
    ui->oldPasswordErrorLabel->setText(QString());
    ui->newPasswordErrorLabel->setText(QString());

    if(PasswordHasher::sharedInstance().validatePassword(ui->oldPasswordLineEdit->text(), user->getPasswordHash()))
    {
        QString newPassword = ui->newPasswordLineEdit->text();

        QString error = validateNewPassword(newPassword);

        if(error.isNull())
        {
            user->setPassword(ui->newPasswordLineEdit->text());
            DataManager::sharedInstance().updateUser(*user);
            close();
        }
        else
        {
            ui->newPasswordErrorLabel->setText(error);
        }
    }
    else
    {
        ui->oldPasswordErrorLabel->setText("Old password does not match");
    }
}

QString ChangePasswordDialog::validateNewPassword(const QString &password)
{
    int length = password.length();
    if (length < minPasswordLength || length > maxPasswordLength)
    {
        return QString("Password must be between %1 and %2 characters").arg(minPasswordLength).arg(maxPasswordLength);
    }

    return QString();
}
