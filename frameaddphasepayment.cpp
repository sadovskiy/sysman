#include "frameaddphasepayment.hpp"
#include "ui_frameaddphasepayment.h"

#include <QSqlError>
#include <QDebug>

FrameAddPhasePayment::FrameAddPhasePayment(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddPhasePayment)
{
    ui->setupUi(this);
    connect(ui->pushButtonPayment, SIGNAL(clicked()),
            this, SLOT(addRow()));
}

FrameAddPhasePayment::~FrameAddPhasePayment()
{
    delete ui;
}

void FrameAddPhasePayment::addRow()
{

}

void FrameAddPhasePayment::setModel(QSqlRelationalTableModel *model)
{
    rmodel = model;
}
