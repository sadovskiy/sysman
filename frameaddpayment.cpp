#include "frameaddpayment.hpp"
#include "ui_frameaddpayment.h"

#include <QSqlError>
#include <QDebug>

FrameAddPayment::FrameAddPayment(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddPayment)
{
    ui->setupUi(this);
    connect(ui->pushButtonPayment, SIGNAL(clicked()),
            this, SLOT(addRow()));
}

FrameAddPayment::~FrameAddPayment()
{
    delete ui;
}

void FrameAddPayment::addRow()
{

}

void FrameAddPayment::setModel(QSqlRelationalTableModel *model)
{
    rmodel = model;
}
