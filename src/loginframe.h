#ifndef LOGINFRAME_H
#define LOGINFRAME_H

#include <QFrame>

namespace Ui {
    class LoginFrame;
}

#include <QSharedPointer>

class User;

class LoginFrame : public QFrame
{
    Q_OBJECT
public:
    LoginFrame(QWidget *parent = 0);
    ~LoginFrame();
private:
    Ui::LoginFrame *ui;
private slots:
    void checkLogin();
signals:
    void loginSuccess(const QSharedPointer<User> &);
};

#endif // LOGINFRAME_H
