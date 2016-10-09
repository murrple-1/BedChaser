#ifndef EDITUSERDIALOG_H
#define EDITUSERDIALOG_H

#include <QDialog>

namespace Ui {
    class EditUserDialog;
}

class User;

class EditUserDialog : public QDialog
{
    Q_OBJECT
public:
    EditUserDialog(User *, QWidget *parent = 0);
    ~EditUserDialog();
private:
    Ui::EditUserDialog *ui;
    User *user;
public slots:
    void updateUser();
};

#endif // EDITUSERDIALOG_H
