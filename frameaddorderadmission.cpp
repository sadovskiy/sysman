#include "frameaddorderadmission.hpp"
#include "ui_frameaddorderadmission.h"

#include <QSqlError>
#include <QDebug>
#include <QMapIterator>

FrameAddOrderAdmission::FrameAddOrderAdmission(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddOrderAdmission)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);


}

FrameAddOrderAdmission::~FrameAddOrderAdmission()
{
    delete ui;
}

void FrameAddOrderAdmission::addRow()
{
}

void FrameAddOrderAdmission::loadData(QMap<int, Department *> &departmentList, const int num)
{
    QMapIterator<int, Department *> idepart(departmentList);

    while (idepart.hasNext()) {
        idepart.next();
        ui->comboBoxDepartmentInst->addItem(idepart.value()->getDepShort());
    }

    QSqlQuery query;
    query.exec(QString("SELECT * FROM orders_admission WHERE order_admission_id = %1").arg(num));

    if (query.lastError().isValid())
        qDebug() << query.lastError().text();

    query.first();
    ui->lineEditOrderAdmissionNum->setText(query.value(1).toString());
    ui->dateEditDateOfOrderAdmission->setDate(query.value(2).toDate());

    int indexDepartment = query.value(3).toInt();
    QMapIterator<int, Department *> idp(departmentList);
    QString idepartament;
    while (idp.hasNext()) {
        idp.next();
        if (idp.key() == indexDepartment)
            idepartament = idp.value()->getDepShort();
    }
    ui->comboBoxDepartmentInst->setCurrentText(idepartament);
    ui->comboBoxDepartmentInst->setCurrentIndex(idp.key());
    ui->lineEditCoursesEnrollment->setText(query.value(4).toString());
    ui->lineEditGroup->setText(query.value(5).toString());

    qDebug() << query.value(1).toString();
}

void FrameAddOrderAdmission::on_pushButton_clicked()
{

}
