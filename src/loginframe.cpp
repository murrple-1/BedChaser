#include "loginframe.h"
#include "ui_loginframe.h"

#include "datamanager.h"

LoginFrame::LoginFrame(QWidget *parent) :
    QFrame(parent), ui(new Ui::LoginFrame)
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

    QSharedPointer<User> user = DataManager::sharedInstance().getUser(username);

    if(!user.isNull() && user->getPassword() == password)
    {
        // TODO
    }
    else
    {
        ui->errorLabel->setText("Error logging on, username incorrect");
    }
}
