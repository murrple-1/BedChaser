#include "searchwindow.h"
#include "ui_searchwindow.h"

#include <QCompleter>

#include "datamanager.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindow),
    chosenObject(NULL)
{
    ui->setupUi(this);

    connect(ui->searchField, &QLineEdit::textEdited, this, &SearchWindow::updateSearchResults);
    connect(ui->searchField, &QLineEdit::returnPressed, this, &SearchWindow::updateSearchResults);

    QStringList completerList;

    // TODO fill completer list

    QCompleter *completer = new QCompleter(completerList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setMaxVisibleItems(10);
    ui->searchField->setCompleter(completer);

    connect(completer, static_cast<void (QCompleter:: *)(const QString &)>(&QCompleter::activated), this, &SearchWindow::updateSearchResults);
    connect(ui->listView, &QListView::doubleClicked, this, &SearchWindow::choseObject);
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

const QSharedPointer<QObject> & SearchWindow::getChosenObject() const
{
    return chosenObject;
}

void SearchWindow::choseObject(const QModelIndex &i)
{
    chosenObject = objects.value(i.data().toString());

    accept();
}

void SearchWindow::updateSearchResults()
{
    ui->listView->setModel(ui->searchField->completer()->completionModel());
}
