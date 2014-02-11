#include "loginframe.h"
#include "ui_loginframe.h"
#include "../core/datamanager.h"
#include "graphicsthread.h"
#include "mapframe.h"

#include "mainwindow.h"

LoginFrame::LoginFrame(QWidget *parent) :
        QFrame(parent),
        ui(new Ui::LoginFrame)
{
    ui->setupUi(this);

    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(checkLogin()));

    //MainWindow::ui->menuTools->setEnabled(false);

    QPixmap pixmap;
    pixmap.load("../deplib/Login_Banner.jpg");
    ui->logoLabel->setPixmap(pixmap);
    ui->logoLabel->setFixedSize(pixmap.size());

    ui->gridLayout->setContentsMargins(QMargins(0, 0, 0, 0));
    setFixedWidth(ui->logoLabel->width());
    setFixedWidth(300);
}

LoginFrame::~LoginFrame()
{
    delete ui;
}

void LoginFrame::checkLogin() {

    QString username = ui->usernameField->text();

    LHIN::User * u = LHIN::DataManager::getDataManager().getUser(username);

    if(u != NULL)
    {
        checkPass();
        delete u;
    } else {
        ui->errorLabel->setText("Error logging on, username incorrect");
    }
}

void LoginFrame::checkPass()
{
    QString username = ui->usernameField->text();
    QString password = ui->passwordField->text();

    LHIN::User * u = LHIN::DataManager::getDataManager().getUser(username);

    if(u->getPassword()==password.toStdString())
    {
        delete LHIN::GraphicsThread::getCurrentWindow()->centralWidget();
        MapFrame * mf = new MapFrame();
        LHIN::GraphicsThread::setCurrentWindowView(mf);
        LHIN::GraphicsThread::getCurrentWindow()->setCurrentUser(u);
    }
    else
    {
        ui->errorLabel->setText("Error logging on, password incorrect");
        delete u;
    }
}
