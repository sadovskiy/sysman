#include "mainwindow.hpp"
#include "dialogconnecttodatabase.hpp"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QSqlRecord>
#include <QModelIndex>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qApp->installTranslator(&appTranslator);
    appTranslator.load("/home/keeper_b/devprogs/sysman/sysman_translation_ru_RU.qm");

    ui->retranslateUi(this);

    if (QSqlDatabase::isDriverAvailable("QPSQL"))
        qDebug() << "SUCCESS: PostgreSQL Database driver found." << endl;
    else
        qDebug() << "FAILURE: No PostgreSQL Database driver available." << endl;

    // Развернуть всё дерево
    ui->treeWidget->expandAll();

    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(closeTab(int)));

    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this, SLOT(itemTabNewOrOpen(QTreeWidgetItem*,int)));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(setCurrentItem(int)));

    // Прячем первую колонку списка так как там хранятся названия таблиц БД
    ui->treeWidget->hideColumn(1);

 //    tableView->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);

//    connect(ui->tableView->horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customHeaderMenuRequested(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    DialogConnectToDataBase dialogConnectToDataBase;
    int result = dialogConnectToDataBase.exec();

    if (result == DialogConnectToDataBase::Accepted) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

        db.setHostName("217.172.21.199");
        db.setDatabaseName("smdb");
        db.setUserName(dialogConnectToDataBase.getUserName());
        db.setPassword(dialogConnectToDataBase.getPassword());

        if (!db.open()) {
            qDebug() << db.lastError().text();
            ui->statusBar->showMessage(db.lastError().text());
            ui->actionConnect->setChecked(false);
        }
        else
            ui->treeWidget->setEnabled(true);
    }
    if (result == DialogConnectToDataBase::Rejected)
        ui->actionConnect->setChecked(false);
    {
        QSqlDatabase db = QSqlDatabase::database();
        if (db.isOpen())
            ui->actionConnect->setChecked(true);

        QSqlQuery query("SELECT * FROM country_table");

        if (!query.isActive())
            QMessageBox::warning(this, tr("Database Error"),
                                 query.lastError().text());

        while(query.next()){
            countryList.append(Country(query.value(0).toInt(),
                                       query.value(1).toString(),
                                       query.value(2).toString(),
                                       query.value(3).toString(),
                                       query.value(4).toString(),
                                       query.value(5).toInt()));
        }
        for (int i = 0; i < countryList.count(); i++) {
            qDebug() << countryList[i].nCodeCountry() << " "
                     << countryList[i].a2CodeCountry() << " "
                     << countryList[i].a3CodeCountry() << " "
                     << countryList[i].c3CodeCountry() << " "
                     << countryList[i].comm() << " "
                     << countryList[i].tCode();
        }
    }
}

void MainWindow::update()
{

}

void MainWindow::closeTab(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::itemTabNewOrOpen(QTreeWidgetItem *item, int col)
{
    int flag = -1;
    TableViewTabForm *tableviewtab = 0;

    for (int i = 0; i < ui->tabWidget->count(); i++)
        if (ui->tabWidget->widget(i)->windowTitle() == item->text(col))
            flag = i;

    if (flag != -1)
        ui->tabWidget->setCurrentIndex(flag);
    else {
        tableviewtab = new TableViewTabForm(this);
        tableviewtab->setWindowTitle(item->text(col));
        ui->tabWidget->addTab(tableviewtab, item->text(col));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    }
    tableviewtab = qobject_cast<TableViewTabForm *>(ui->tabWidget->currentWidget());
    tableviewtab->clear();
    tableviewtab->setTableName(item->text(1));
}

void MainWindow::setCurrentItem(int index)
{
    if (index != -1) {
        QString s = ui->tabWidget->widget(index)->windowTitle();
        QList<QTreeWidgetItem*> items;
        items = ui->treeWidget->findItems(s, Qt::MatchRecursive, 0);
        if (!items.isEmpty())
            ui->treeWidget->setCurrentItem(items.at(0));
    }
}
