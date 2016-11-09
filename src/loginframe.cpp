#include "loginframe.h"
#include "ui_loginframe.h"

#include "datamanager.h"
#include "passwordhasher.h"

LoginFrame::LoginFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LoginFrame)
{
    ui->setupUi(this);

    QPixmap pixmap;
    pixmap.load("images/Login_Banner.jpg");
    ui->logoLabel->setPixmap(pixmap);
    ui->logoLabel->setAlignment(Qt::AlignCenter);

    connect(ui->usernameLineEdit, &QLineEdit::returnPressed, this, &LoginFrame::checkLogin);
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, this, &LoginFrame::checkLogin);
    connect(ui->loginPushButton, &QPushButton::clicked, this, &LoginFrame::checkLogin);
}

LoginFrame::~LoginFrame()
{
    delete ui;
}

void LoginFrame::checkLogin()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    QSharedPointer<User> user;
    {
        QMap<QString, QVariant> whereParams;
        whereParams.insert(":login", username);
        QList<QSharedPointer<User> > _users = DataManager::sharedInstance().getUsers("`login` = :login", whereParams, QString(), 1, 0);
        if(_users.length() == 1)
        {
            user = _users.first();
        }
    }

    if(!user.isNull() && PasswordHasher::sharedInstance().validatePassword(password, user->getPasswordHash()))
    {
        emit loginSuccess(user);
    }
    else
    {
        ui->errorLabel->setText("Username or password not recognized");
    }
}
