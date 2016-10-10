#ifndef EDITUSERDIALOG_H
#define EDITUSERDIALOG_H

#include <QDialog>

namespace Ui {
    class EditUserDialog;
}

#include <QSharedPointer>

class User;

class EditUserDialog : public QDialog
{
    Q_OBJECT
public:
    EditUserDialog(const QSharedPointer<User> &, QWidget *parent = 0);
    ~EditUserDialog();
private:
    Ui::EditUserDialog *ui;

    QSharedPointer<User> user;
public slots:
    void updateUser();
};

#endif // EDITUSERDIALOG_H
