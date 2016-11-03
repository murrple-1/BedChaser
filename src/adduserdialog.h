#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>

namespace Ui {
    class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT
public:
    AddUserDialog(QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    ~AddUserDialog();
private:
    Ui::AddUserDialog *ui;
public slots:
    void addUser();
};

#endif // ADDUSERDIALOG_H
