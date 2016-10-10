#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
    class ChangePasswordDialog;
}

#include <QSharedPointer>

class User;

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT
public:
    ChangePasswordDialog(const QSharedPointer<User> &, QWidget *parent = 0);
    ~ChangePasswordDialog();
private:
    Ui::ChangePasswordDialog *ui;

    QSharedPointer<User> user;
public slots:
    void updateUser();
};

#endif // CHANGEPASSWORDDIALOG_H
