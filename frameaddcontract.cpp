#include "frameaddcontract.hpp"
#include "ui_frameaddcontract.h"

#include <QSqlError>
#include <QDebug>

FrameAddContract::FrameAddContract(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddContract)
{
    ui->setupUi(this);

    //ui->treeWidgetContract->addAction(new QAction("query.value(1).toString()", this));
}

FrameAddContract::~FrameAddContract()
{
    delete ui;
}

void FrameAddContract::setModel(QSqlQuery *query)
{

}

void FrameAddContract::loadData(const int numStr)
{
    QSqlQuery query;
    query.exec(QString("SELECT * FROM contract AS ctr WHERE contract_id = %1").arg(numStr));

        if (query.lastError().isValid())
            qDebug() << query.lastError().text();

        query.first();
        ui->lineEditContractNumber->setText(query.value(1).toString());
        ui->dateEditContractDate->setDate(query.value(2).toDate());
        ui->lineEditPayment->setText(query.value(3).toString());
        ui->comboBoxDepartmentContract->setCurrentText(query.value(4).toString());
        ui->comboBoxDurationOfStudy->setCurrentText(query.value(4).toString());
        ui->comboBoxAcademicProgram->setCurrentText(query.value(5).toString());
        ui->comboBoxContractType->setCurrentText(query.value(6).toString());

        qDebug() << query.value(1).toString();
}
