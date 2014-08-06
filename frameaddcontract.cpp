#include "frameaddcontract.hpp"
#include "ui_frameaddcontract.h"

#include <QSqlError>
#include <QDebug>

FrameAddContract::FrameAddContract(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddContract)
{
    ui->setupUi(this);
    connect(ui->pushButtonContract, SIGNAL(clicked()),
            this, SLOT(addRow()));
}

FrameAddContract::~FrameAddContract()
{
    delete ui;
}

void FrameAddContract::addRow()
{
    int row = rmodel->rowCount();
}

void FrameAddContract::setModel(QSqlRelationalTableModel *model)
{
    rmodel = model;
}
