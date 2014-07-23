#include "mainwindow.hpp"
#include "dialogconnecttodatabase.hpp"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QSqlRecord>
#include <QMenu>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qApp->installTranslator(&appTranslator);
    appTranslator.load("/home/keeper_b/devprogs/sysman/test_ru_RU.qm");
    proxyModel = new QSortFilterProxyModel(this);
    ui->retranslateUi(this);
    ui->treeWidget->expandAll();
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
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

            rmodel1 = new QSqlRelationalTableModel(this);
            rmodel1->setTable("all_data");
            rmodel1->select();
            ui->tableView->setModel(rmodel1);
//            pHeader = new QHeaderView(Qt::Horizontal);
            ui->tableView->resizeColumnsToContents();
            rmodel2 = new QSqlRelationalTableModel(this);
            rmodel2->setTable("student_table");
            rmodel2->select();
            ui->tableView_2->setModel(rmodel2);
            ui->tableView_2->resizeColumnsToContents();
            rmodel3 = new QSqlRelationalTableModel(this);
            rmodel3->setTable("orders_table");
            rmodel3->select();
            ui->tableView_3->setModel(rmodel3);
            ui->tableView_3->resizeColumnsToContents();
            rmodel4 = new QSqlRelationalTableModel(this);
            rmodel4->setTable("payment_table");
            rmodel4->select();
            proxyModel->setSourceModel(rmodel4);
            ui->tableView_4->setModel(proxyModel);
            ui->tableView_4->resizeColumnsToContents();
            connect(rmodel1, SIGNAL(beforeUpdate(int,QSqlRecord&)), this, SLOT(update()));
            connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(update()));
            connect(rmodel3, SIGNAL(beforeUpdate(int,QSqlRecord&)), this, SLOT(update()));
            connect(rmodel4, SIGNAL(beforeUpdate(int,QSqlRecord&)), this, SLOT(update()));



            ui->tableView->hideColumn(rmodel1->fieldIndex("id_student"));
            ui->tableView_2->hideColumn(rmodel2->fieldIndex("id_student"));
            ui->tableView_3->hideColumn(rmodel3->fieldIndex("id_order"));
            ui->tableView_4->hideColumn(rmodel4->fieldIndex("id_payment"));

            rmodel1->setHeaderData(rmodel1->fieldIndex("order_admission_num"), Qt::Horizontal, tr("order_admission_num"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("order_dismissal_num"), Qt::Horizontal, tr("order_dismissal_num"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("date_of_order_admission"), Qt::Horizontal, tr("date_of_order_admission"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("date_of_order_dismissal"), Qt::Horizontal, tr("date_of_order_dismissal"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("amount"), Qt::Horizontal, tr("amount"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("semester"), Qt::Horizontal, tr("semester"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("discount"), Qt::Horizontal, tr("discount"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("actual_amount_of_payment"), Qt::Horizontal, tr("actual_amount_of_payment"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("date_of_pay"), Qt::Horizontal, tr("date_of_pay"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("penalties"), Qt::Horizontal, tr("penalties"));


            rmodel1->setHeaderData(rmodel1->fieldIndex("contract_number"), Qt::Horizontal, tr("contract_number"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("contract_date"), Qt::Horizontal, tr("contract_date"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("contract_type"), Qt::Horizontal, tr("contract_type"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("surname"), Qt::Horizontal, tr("surname"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("name"), Qt::Horizontal, tr("name"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("patronym"), Qt::Horizontal, tr("patronym"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("Sex"), Qt::Horizontal, tr("Sex"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("date_of_birth"), Qt::Horizontal, tr("date_of_birth"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("place_of_birth"), Qt::Horizontal, tr("place_of_birth"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("citizenship"), Qt::Horizontal, tr("citizenship"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("passport_series"), Qt::Horizontal, tr("passport_series"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("passport_number"), Qt::Horizontal, tr("passport_number"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("passport_authority"), Qt::Horizontal, tr("passport_authority"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("passport_date_of_issue"), Qt::Horizontal, tr("passport_date_of_issue"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("passport_subdivision_code"), Qt::Horizontal, tr("passport_subdivision_code"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("registration_adm_unit"), Qt::Horizontal, tr("registration_adm_unit"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("registration_adress"), Qt::Horizontal, tr("registration_adress"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("registration_date"), Qt::Horizontal, tr("registration_date"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("postcode"), Qt::Horizontal, tr("postcode"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("phone"), Qt::Horizontal, tr("phone"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("email"), Qt::Horizontal, tr("email"));
            rmodel1->setHeaderData(rmodel1->fieldIndex("individual_taxpayer_identification_number"), Qt::Horizontal, tr("individual_taxpayer_identification_number"));

            rmodel2->setHeaderData(rmodel2->fieldIndex("contract_number"), Qt::Horizontal, tr("contract_number"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("contract_date"), Qt::Horizontal, tr("contract_date"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("contract_type"), Qt::Horizontal, tr("contract_type"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("surname"), Qt::Horizontal, tr("surname"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("name"), Qt::Horizontal, tr("name"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("patronym"), Qt::Horizontal, tr("patronym"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("Sex"), Qt::Horizontal, tr("Sex"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("date_of_birth"), Qt::Horizontal, tr("date_of_birth"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("place_of_birth"), Qt::Horizontal, tr("place_of_birth"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("citizenship"), Qt::Horizontal, tr("citizenship"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("passport_series"), Qt::Horizontal, tr("passport_series"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("passport_number"), Qt::Horizontal, tr("passport_number"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("passport_authority"), Qt::Horizontal, tr("passport_authority"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("passport_date_of_issue"), Qt::Horizontal, tr("passport_date_of_issue"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("passport_subdivision_code"), Qt::Horizontal, tr("passport_subdivision_code"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("registration_adm_unit"), Qt::Horizontal, tr("registration_adm_unit"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("registration_adress"), Qt::Horizontal, tr("registration_adress"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("registration_date"), Qt::Horizontal, tr("registration_date"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("postcode"), Qt::Horizontal, tr("postcode"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("phone"), Qt::Horizontal, tr("phone"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("email"), Qt::Horizontal, tr("email"));
            rmodel2->setHeaderData(rmodel2->fieldIndex("individual_taxpayer_identification_number"), Qt::Horizontal, tr("individual_taxpayer_identification_number"));

            rmodel3->setHeaderData(rmodel3->fieldIndex("order_admission_num"), Qt::Horizontal, tr("order_admission_num"));
            rmodel3->setHeaderData(rmodel3->fieldIndex("order_dismissal_num"), Qt::Horizontal, tr("order_dismissal_num"));
            rmodel3->setHeaderData(rmodel3->fieldIndex("date_of_order_admission"), Qt::Horizontal, tr("date_of_order_admission"));
            rmodel3->setHeaderData(rmodel3->fieldIndex("date_of_order_dismissal"), Qt::Horizontal, tr("date_of_order_dismissal"));

            rmodel4->setHeaderData(rmodel4->fieldIndex("amount"), Qt::Horizontal, tr("amount"));
            rmodel4->setHeaderData(rmodel4->fieldIndex("semester"), Qt::Horizontal, tr("semester"));
            rmodel4->setHeaderData(rmodel4->fieldIndex("discount"), Qt::Horizontal, tr("discount"));
            rmodel4->setHeaderData(rmodel4->fieldIndex("actual_amount_of_payment"), Qt::Horizontal, tr("actual_amount_of_payment"));
            rmodel4->setHeaderData(rmodel4->fieldIndex("date_of_pay"), Qt::Horizontal, tr("date_of_pay"));
            rmodel4->setHeaderData(rmodel4->fieldIndex("penalties"), Qt::Horizontal, tr("penalties"));

            connect(ui->tableView->horizontalHeader(), SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), ui->tableView, SLOT(sortByColumn(int)));
            connect(ui->tableView_2->horizontalHeader(), SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), ui->tableView_2, SLOT(sortByColumn(int)));
            connect(ui->tableView_3->horizontalHeader(), SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), ui->tableView_3, SLOT(sortByColumn(int)));
            connect(ui->tableView_4->horizontalHeader(), SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), ui->tableView_4, SLOT(sortByColumn(int)));
            ui->tableView_4->setContextMenuPolicy(Qt::CustomContextMenu);

            connect(ui->tableView_4->horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(CrMenu()));

//            ui->tableView_4->setHorizontalHeader(pHeader);


            /*
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
            */
        }
    }
    else
        qDebug() << "FAILURE: No PostgreSQL Database driver available." << endl;
}

void MainWindow::update()
{
    rmodel1->select();
    rmodel2->select();
    rmodel3->select();
    rmodel4->select();
}

void MainWindow::closeTab(int Index)
{
    ui->tabWidget->removeTab(Index);
}

void MainWindow::CrMenu()
{
    QMenu *mymenu = new QMenu(ui->tableView_4);
    mymenu->addAction("Show");
    mymenu->addAction("Hide");
    mymenu->exec();

}
