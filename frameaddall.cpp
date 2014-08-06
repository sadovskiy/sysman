#include "frameaddall.hpp"
#include "ui_frameaddall.h"

#include <QSqlError>
#include <QDebug>

FrameAddAll::FrameAddAll(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddAll)
{
    ui->setupUi(this);
/*    connect(ui->pushButtonAddR, SIGNAL(clicked()),
            this, SLOT(addRow()));*/
}

FrameAddAll::~FrameAddAll()
{
    delete ui;
}

void FrameAddAll::addRow()
{
    int row = rmodel->rowCount();
//     rmodel->setData(rmodel->index(row, rmodel->fieldIndex("")), ui->->());
}

void FrameAddAll::setModel(QSqlRelationalTableModel *model)
{
    rmodel = model;
}
