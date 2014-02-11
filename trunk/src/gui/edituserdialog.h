#ifndef EDITUSERDIALOG_H
#define EDITUSERDIALOG_H

#include <QDialog>
#include "../core/user.h"

namespace Ui {
    class EditUserDialog;
}

class EditUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserDialog(LHIN::User * const, QWidget *parent = 0);
    ~EditUserDialog();

public slots:
    void updateUser();

private:
    Ui::EditUserDialog *ui;
    LHIN::User * user;
};

#endif // EDITUSERDIALOG_H
