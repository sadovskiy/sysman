#include "frameaddorderadmission.hpp"
#include "ui_frameaddorderadmission.h"

#include <QSqlError>
#include <QDebug>

FrameAddOrderAdmission::FrameAddOrderAdmission(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddOrderAdmission)
{
    ui->setupUi(this);
    connect(ui->pushButtonAROA, SIGNAL(clicked()),
            this, SLOT(addRow()));
}

FrameAddOrderAdmission::~FrameAddOrderAdmission()
{
    delete ui;
}

void FrameAddOrderAdmission::addRow()
{
    int row = rmodel->rowCount();
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("order_admission_num")), ui->lineEditOrderAdmissionNum->text());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("date_of_order_admission")), ui->dateEditDateOfOrderAdmission->date());

    rmodel->submitAll();

    qDebug() << rmodel->lastError().text();
}

void FrameAddOrderAdmission::setModel(QSqlRelationalTableModel *model)
{
    rmodel = model;
}
