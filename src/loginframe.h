#ifndef LOGINFRAME_H
#define LOGINFRAME_H

#include <QFrame>

namespace Ui {
    class LoginFrame;
}

class LoginFrame : public QFrame
{
    Q_OBJECT
public:
    LoginFrame(QWidget *parent = 0);
    ~LoginFrame();
private:
    Ui::LoginFrame *ui;
public slots:
    void checkLogin();
};

#endif // LOGINFRAME_H
