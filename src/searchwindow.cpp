#include "searchwindow.h"
#include "ui_searchwindow.h"

#include <QDebug>

#include "datamanager.h"
#include "region.h"
#include "facility.h"
#include "patient.h"
#include "user.h"

static const int ObjectTypeRole = Qt::UserRole + 1;
static const int ObjectIdRole = Qt::UserRole + 2;

typedef enum _ObjectType
{
    ObjectTypeRegion,
    ObjectTypeFacility,
    ObjectTypePatient,
    ObjectTypeUser
} ObjectType;

SearchWindow::SearchWindow(UserType userType, QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::SearchWindow),
    userType(userType),
    chosenObject(NULL)
{
    ui->setupUi(this);

    connect(ui->searchLineEdit, &QLineEdit::returnPressed, this, &SearchWindow::searchLineEditReturnPressed);
    connect(ui->listWidget, &QListWidget::doubleClicked, this, &SearchWindow::choseObject);
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

const QSharedPointer<QObject> & SearchWindow::getChosenObject() const
{
    return chosenObject;
}

void SearchWindow::choseObject(const QModelIndex &index)
{
    QMap<QString, QVariant> whereParams;
    whereParams.insert(":id", index.data(ObjectIdRole));

    ObjectType objectType = (ObjectType) index.data(ObjectTypeRole).toInt();
    switch(objectType)
    {
    case ObjectTypeRegion:
        chosenObject = DataManager::sharedInstance().getRegions("`id` = :id", whereParams, QString(), 1).first();
        break;
    case ObjectTypeFacility:
        chosenObject = DataManager::sharedInstance().getFacilities("`id` = :id", whereParams, QString(), 1).first();
        break;
    case ObjectTypePatient:
        chosenObject = DataManager::sharedInstance().getPatients("`id` = :id", whereParams, QString(), 1).first();
        break;
    case ObjectTypeUser:
        chosenObject = DataManager::sharedInstance().getUsers("`id` = :id", whereParams, QString(), 1).first();
        break;
    default:
        qWarning() << "Unknown user type";
        break;
    }


    accept();
}

void SearchWindow::searchLineEditReturnPressed()
{
    ui->listWidget->clear();

    QString searchString = ui->searchLineEdit->text();
    QString sqlSearchString = QString("%%1%").arg(searchString);

    {
        QMap<QString, QVariant> whereParams;
        whereParams.insert(":name", sqlSearchString);
        QList<QSharedPointer<Region> > regions = DataManager::sharedInstance().getRegions("`name` LIKE :name", whereParams, "`id` ASC");
        foreach(const QSharedPointer<Region> &region, regions)
        {
            QString completerString = QString("Region - %1").arg(region->getName());
            QListWidgetItem *item = new QListWidgetItem(completerString);
            item->setData(ObjectTypeRole, ObjectTypeRegion);
            item->setData(ObjectIdRole, region->getID());
            ui->listWidget->addItem(item);
        }
    }

    {
        QMap<QString, QVariant> whereParams;
        whereParams.insert(":name", sqlSearchString);
        QList<QSharedPointer<Facility> > facilities = DataManager::sharedInstance().getFacilities("`name` LIKE :name", whereParams, "`id` ASC");
        foreach(const QSharedPointer<Facility> &facility, facilities)
        {
            QString completerString = QString("Facility - %1").arg(facility->getName());
            QListWidgetItem *item = new QListWidgetItem(completerString);
            item->setData(ObjectTypeRole, ObjectTypeFacility);
            item->setData(ObjectIdRole, facility->getID());
            ui->listWidget->addItem(item);
        }
    }

    {
        QMap<QString, QVariant> whereParams;
        whereParams.insert(":name", sqlSearchString);
        QList<QSharedPointer<Patient> > patients = DataManager::sharedInstance().getPatients("`name` LIKE :name", whereParams, "`id` ASC");
        foreach(const QSharedPointer<Patient> &patient, patients)
        {
            QString completerString = QString("Patient - %1: %2").arg(patient->getName()).arg(patient->getHealthCareNumber());
            QListWidgetItem *item = new QListWidgetItem(completerString);
            item->setData(ObjectTypeRole, ObjectTypePatient);
            item->setData(ObjectIdRole, patient->getID());
            ui->listWidget->addItem(item);
        }
    }

    if(userType >= UserTypeSystemAdmin)
    {
        {
            QMap<QString, QVariant> whereParams;
            whereParams.insert(":login", sqlSearchString);
            QList<QSharedPointer<User> > users = DataManager::sharedInstance().getUsers("`login` LIKE :login", whereParams, "`id` ASC");
            foreach(const QSharedPointer<User> &user, users)
            {
                QString completerString = QString("User - %1").arg(user->getUsername());
                QListWidgetItem *item = new QListWidgetItem(completerString);
                item->setData(ObjectTypeRole, ObjectTypeUser);
                item->setData(ObjectIdRole, user->getId());
                ui->listWidget->addItem(item);
            }
        }
    }
}
