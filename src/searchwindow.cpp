#include "searchwindow.h"
#include "ui_searchwindow.h"

#include <QStringListModel>

#include "datamanager.h"

#include "region.h"
#include "facility.h"
#include "patient.h"
#include "user.h"

SearchWindow::SearchWindow(UserType userType, QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::SearchWindow),
    chosenObject(NULL)
{
    ui->setupUi(this);

    QList<QSharedPointer<Region> > regions = DataManager::sharedInstance().getRegions(QString(), QMap<QString, QVariant>(), "`id` DESC", 100, 0);
    foreach(const QSharedPointer<Region> &region, regions)
    {
        QString completerString = region->getName();
        addObject("Region", completerString, region);
    }

    QList<QSharedPointer<Facility> > facilities = DataManager::sharedInstance().getFacilities(QString(), QMap<QString, QVariant>(), "`id` DESC", 100, 0);
    foreach(const QSharedPointer<Facility> &facility, facilities)
    {
        QString completerString = facility->getName();
        addObject("Facility", completerString, facility);
    }

    QList<QSharedPointer<Patient> > patients = DataManager::sharedInstance().getPatients(QString(), QMap<QString, QVariant>(), "`id` DESC", 100, 0);
    foreach(const QSharedPointer<Patient> &patient, patients)
    {
        QString completerString = QString("%1: %2").arg(patient->getName()).arg(patient->getHealthCardNumber());
        addObject("Patient", completerString, patient);
    }

    if(userType >= UserTypeSystemAdmin)
    {
        QList<QSharedPointer<User> > users = DataManager::sharedInstance().getUsers(QString(), QMap<QString, QVariant>(), "`id` DESC", 100, 0);
        foreach(const QSharedPointer<User> &user, users)
        {
            QString completerString = user->getUsername();
            addObject("User", completerString, user);
        }
    }

    searchLineEditChanged(QString());

    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &SearchWindow::searchLineEditChanged);
    connect(ui->listView, &QListView::doubleClicked, this, &SearchWindow::choseObject);
    connect(ui->donePushButton, &QPushButton::clicked, this, &SearchWindow::reject);
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::addObject(const QString &prefix, const QString &name, const QSharedPointer<QObject> &obj)
{
    QString fullName = QString("%1 - %2").arg(prefix).arg(name);
    objects.insert(fullName, obj);
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

void SearchWindow::searchLineEditChanged(const QString &text)
{
    QStringList currentFullNames;
    foreach(const QString &key, objects.keys())
    {
        if(key.contains(text, Qt::CaseInsensitive))
        {
            currentFullNames.append(key);
        }
    }

    QAbstractItemModel *oldModel = ui->listView->model();
    ui->listView->setModel(new QStringListModel(currentFullNames, this));

    if(oldModel != NULL)
    {
        delete oldModel;
    }
}
