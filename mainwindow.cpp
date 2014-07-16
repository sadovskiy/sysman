#include "mainwindow.hpp"
#include "dialogconnecttodatabase.hpp"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->expandAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    if (QSqlDatabase::isDriverAvailable("QPSQL")) {
        qDebug() << "SUCCESS: PostgreSQL Database driver found." << endl;
        DialogConnectToDataBase dialogConnectToDataBase;
        int result = dialogConnectToDataBase.exec();

        if (result == DialogConnectToDataBase::Accepted) {
            QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

            db.setHostName("217.172.21.199");
            db.setDatabaseName("sysmandb");
            db.setUserName(dialogConnectToDataBase.getUserName());
            db.setPassword(dialogConnectToDataBase.getPassword());

            if (!db.open()) {
                qDebug() << db.lastError().text();
                ui->statusBar->showMessage(db.lastError().text());
            }
        }
    }
    else
        qDebug() << "FAILURE: No PostgreSQL Database driver available." << endl;
}
