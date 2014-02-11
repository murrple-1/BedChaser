#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H

#include <QDialog>
#include "../core/user.h"

namespace Ui {
    class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordDialog(LHIN::User * const, QWidget *parent = 0);
    ~ChangePasswordDialog();

public slots:
    void updateUser();

private:
    Ui::ChangePasswordDialog *ui;
    LHIN::User * user;
};

#endif // CHANGEPASSWORDDIALOG_H
