#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>
#include <QStringList>
#include <QCompleter>
#include <QStringListModel>
#include <map>

#include "../core/datamanager.h"

namespace Ui {
    class SearchWindow;
}

class SearchWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindow(const std::list<LHIN::DataManager::OBJECTS> &, QWidget *parent = 0);
    ~SearchWindow();
    LHIN::Object * getChosenObject() const;

public slots:
    void UpdateSearchResults();
    void ChoseObject(QModelIndex);

private:
    void setupCompleter();

    Ui::SearchWindow *ui;
    std::map<QString, LHIN::Object *> obj;
    QCompleter *completer;
    LHIN::Object * chosenObject;
};

#endif // SEARCHWINDOW_H
