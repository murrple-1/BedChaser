#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>

namespace Ui {
    class SearchWindow;
}

#include <QList>
#include <QMap>
#include <QSharedPointer>

#include "user.h"

class SearchWindow : public QDialog
{
    Q_OBJECT
public:
    SearchWindow(UserType userType, QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    ~SearchWindow();

    const QSharedPointer<QObject> & getChosenObject() const;
private:
    void addObject(const QString &prefix, const QString &name, const QSharedPointer<QObject> &);
    Ui::SearchWindow *ui;

    QMap<QString, QSharedPointer<QObject> > objects;
    QSharedPointer<QObject> chosenObject;
private slots:
    void searchLineEditChanged(const QString &);
    void choseObject(const QModelIndex &);
};

#endif // SEARCHWINDOW_H
