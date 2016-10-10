#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>

namespace Ui {
    class SearchWindow;
}

#include <QList>
#include <QMap>
#include <QSharedPointer>

class SearchWindow : public QDialog
{
    Q_OBJECT
public:
    SearchWindow(QWidget *parent = 0);
    ~SearchWindow();

    const QSharedPointer<QObject> & getChosenObject() const;
private:
    Ui::SearchWindow *ui;

    QMap<QString, QSharedPointer<QObject> > objects;
    QSharedPointer<QObject> chosenObject;
public slots:
    void updateSearchResults();
    void choseObject(const QModelIndex &);
};

#endif // SEARCHWINDOW_H
