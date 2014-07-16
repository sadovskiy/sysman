#include "mainwindow.hpp"
#include "dialogconnecttodatabase.hpp"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QSqlRecord>

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
            rmodel = new QSqlRelationalTableModel(this);
            rmodel->setTable("country_table");
            rmodel->select();
            ui->tableWidget->setColumnCount(rmodel->columnCount());
            ui->tableWidget->setRowCount(rmodel->rowCount());

            for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
                QSqlRecord record = rmodel->record(row);

                    QTableWidgetItem *newItem0 = new QTableWidgetItem(record.value(0).toString());
                    QTableWidgetItem *newItem1 = new QTableWidgetItem(record.value(1).toString());
                    QTableWidgetItem *newItem2 = new QTableWidgetItem(record.value(2).toString());
                    QTableWidgetItem *newItem3 = new QTableWidgetItem(record.value(3).toString());
                    QTableWidgetItem *newItem4 = new QTableWidgetItem(record.value(4).toString());
                    ui->tableWidget->setItem(row, 0, newItem0);
                    ui->tableWidget->setItem(row, 1, newItem1);
                    ui->tableWidget->setItem(row, 2, newItem2);
                    ui->tableWidget->setItem(row, 3, newItem3);
                    ui->tableWidget->setItem(row, 4, newItem4);
                    newItem2->setBackgroundColor(QColor(Qt::green));
            }
        }
    }
    else
        qDebug() << "FAILURE: No PostgreSQL Database driver available." << endl;
}
