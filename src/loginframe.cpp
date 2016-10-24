#include "loginframe.h"
#include "ui_loginframe.h"

#include "datamanager.h"

LoginFrame::LoginFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LoginFrame)
{
    ui->setupUi(this);

    ui->verticalLayout->setContentsMargins(QMargins(0, 0, 0, 0));

    QPixmap pixmap;
    pixmap.load("images/Login_Banner.jpg");
    ui->logoLabel->setPixmap(pixmap);
    ui->logoLabel->setFixedSize(pixmap.size());

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginFrame::checkLogin);
}

LoginFrame::~LoginFrame()
{
    delete ui;
}

void LoginFrame::checkLogin()
{
    QString username = ui->usernameField->text();
    QString password = ui->passwordField->text();

    // TODO hash the password
    QString passwordHash = password;

    QSharedPointer<User> user;
    {
        QMap<QString, QString> whereParams;
        whereParams.insert(":login", username);
        QList<QSharedPointer<User> > _users = DataManager::sharedInstance().getUsers("`login` = :login", whereParams, QString(), 1, 0);
        if(_users.length() == 1)
        {
            user = _users.at(0);
        }
    }

    if(!user.isNull() && user->getPasswordHash() == passwordHash)
    {
        // TODO
    }
    else
    {
        ui->errorLabel->setText("Error logging on, username incorrect");
    }
}
