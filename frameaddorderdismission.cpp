#include "frameaddorderdismission.hpp"
#include "ui_frameaddorderdismission.h"

#include <QSqlError>
#include <QDebug>

FrameAddOrderDismission::FrameAddOrderDismission(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddOrderDismission)
{
    ui->setupUi(this);
    connect(ui->pushButtonAROD, SIGNAL(clicked()),
            this, SLOT(addRow()));
}

FrameAddOrderDismission::~FrameAddOrderDismission()
{
    delete ui;
}

void FrameAddOrderDismission::addRow()
{
    int row = rmodel->rowCount();
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("order_dismissal_num")), ui->lineEditOrderDismissalNumber->text().toInt());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("date_of_order_dismissal")), ui->dateEditOutdateOfOrderDismissal->date());

    rmodel->submitAll();

    qDebug() << rmodel->lastError().text();
}

void FrameAddOrderDismission::setModel(QSqlRelationalTableModel *model)
{
    rmodel = model;
}
