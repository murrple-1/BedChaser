#include "searchwindow.h"
#include "ui_searchwindow.h"

#include <QCompleter>

#include "datamanager.h"

SearchWindow::SearchWindow(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::SearchWindow),
    chosenObject(NULL)
{
    ui->setupUi(this);

    connect(ui->searchLineEdit, &QLineEdit::textEdited, this, &SearchWindow::updateSearchResults);
    connect(ui->searchLineEdit, &QLineEdit::returnPressed, this, &SearchWindow::updateSearchResults);

    QStringList completerList;

    // TODO fill completer list

    QCompleter *completer = new QCompleter(completerList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setMaxVisibleItems(10);
    ui->searchLineEdit->setCompleter(completer);

    connect(completer, static_cast<void (QCompleter:: *)(const QString &)>(&QCompleter::activated), this, &SearchWindow::updateSearchResults);
    connect(ui->listView, &QListView::doubleClicked, this, &SearchWindow::choseObject);
    connect(ui->donePushButton, &QPushButton::clicked, this, &SearchWindow::reject);
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
    ui->listView->setModel(ui->searchLineEdit->completer()->completionModel());
}
