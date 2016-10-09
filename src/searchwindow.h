#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>

#include <QList>
#include <QMap>

namespace Ui {
    class SearchWindow;
}

class SearchWindow : public QDialog
{
    Q_OBJECT
public:
    SearchWindow(QWidget *parent = 0);
    ~SearchWindow();

    QObject * getChosenObject() const;
private:
    Ui::SearchWindow *ui;

    QMap<QString, QObject *> obj;
    QObject *chosenObject;
public slots:
    void updateSearchResults();
    void choseObject(const QModelIndex &);
};

#endif // SEARCHWINDOW_H
