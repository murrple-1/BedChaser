#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "../core/datamanager.h"
SearchWindow::SearchWindow(const std::list<LHIN::DataManager::OBJECTS> & ls, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::SearchWindow),
        chosenObject(NULL)
{
    ui->setupUi(this);
    connect(ui->searchField, SIGNAL(textEdited(QString)), this, SLOT(UpdateSearchResults()));
    connect(ui->searchField, SIGNAL(returnPressed()), this, SLOT(UpdateSearchResults()));

    std::list<LHIN::Object *> * objList = LHIN::DataManager::getDataManager().getObjectList(ls);
    std::list<LHIN::Object *>::const_iterator iter;
    for(iter = objList->begin(); iter != objList->end(); iter++)
    {
        obj.insert(std::pair<QString, LHIN::Object *>(QString((*iter)->toUIString().c_str()), *iter));
    }
    delete objList;
    setupCompleter();
    connect(completer, SIGNAL(activated(QModelIndex)), this, SLOT(ChoseObject(QModelIndex)));
    connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ChoseObject(QModelIndex)));
}

LHIN::Object * SearchWindow::getChosenObject() const
{
    return chosenObject;
}

void SearchWindow::setupCompleter()
{
    QStringList sList;

    std::map<QString, LHIN::Object *>::const_iterator iter;
    for(iter = obj.begin(); iter != obj.end(); iter++)
    {
        sList.push_back(iter->first);
    }

    completer = new QCompleter(sList);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setMaxVisibleItems(10);
    ui->searchField->setCompleter(completer);
}

void SearchWindow::ChoseObject(QModelIndex i)
{
    std::map<QString, LHIN::Object *>::const_iterator iter = obj.find(i.data().toString());
    chosenObject = iter->second;
    close();
}

void SearchWindow::UpdateSearchResults()
{
    ui->listView->setModel(completer->completionModel());
}

SearchWindow::~SearchWindow()
{
    std::map<QString, LHIN::Object *>::const_iterator iter;
    for(iter = obj.begin(); iter != obj.end(); iter++)
    {
        delete iter->second;
    }
    delete completer;
    delete ui;
}
