#include "frameaddcontract.hpp"
#include "ui_frameaddcontract.h"

#include <QSqlError>
#include <QDebug>
#include <QMapIterator>

FrameAddContract::FrameAddContract(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddContract)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);


}

FrameAddContract::~FrameAddContract()
{
    delete ui;
}

void FrameAddContract::loadData(QMap<int, QString> &cntrTypeList, QMap<int, QString> &curriculumList, QMap<int, QString> &yearList, const int numStr)
{
    QMapIterator<int, QString> ict(cntrTypeList);

    while (ict.hasNext()) {
        ict.next();
        ui->comboBoxAcademicProgram->addItem(ict.value());
    }

    QMapIterator<int, QString> idr(curriculumList);

    while (idr.hasNext()) {
        idr.next();
        ui->comboBoxContractType->addItem(idr.value());
    }

    QMapIterator<int, QString> iy(yearList);

    while (iy.hasNext()) {
        iy.next();
        ui->comboBoxDurationOfStudy->addItem(iy.value());
    }
    QSqlQuery query;
    query.exec(QString("SELECT * FROM contract AS ctr WHERE contract_id = %1").arg(numStr));

    if (query.lastError().isValid())
        qDebug() << query.lastError().text();

    query.first();
    ui->lineEditContractNumber->setText(query.value(1).toString());
    ui->dateEditContractDate->setDate(query.value(2).toDate());
    ui->lineEditPayment->setText(query.value(3).toString());

    int indexAP = query.value(5).toInt();
    QMapIterator<int, QString> idict(cntrTypeList);
    QString iCntrTypeList;
    while (idict.hasNext()) {
        idict.next();
        if (idict.key() == indexAP)
            iCntrTypeList = idict.value();
    }
    ui->comboBoxAcademicProgram->setCurrentText(iCntrTypeList);

    int indexCT = query.value(6).toInt();
    QMapIterator<int, QString> idl(curriculumList);
    QString icurriculumList;
    while (idl.hasNext()) {
        idl.next();
        if (idl.key() == indexCT)
            icurriculumList = idl.value();
    }
    ui->comboBoxContractType->setCurrentText(icurriculumList);

    int indexDoS = query.value(6).toInt();
    QMapIterator<int, QString> idys(yearList);
    QString iyearList;
    while (idys.hasNext()) {
        idys.next();
        if (idys.key() == indexDoS)
            iyearList = idys.value();
    }
    ui->comboBoxDurationOfStudy->setCurrentText(iyearList);
}

void FrameAddContract::on_pushButton_clicked()
{
/*    ui->lineEditContractNumber->setText();
    ui->dateEditContractDate->setDate(query.value(2).toDate());
    ui->lineEditPayment->setText(query.value(3).toString());
    ui->comboBoxDepartmentContract->setCurrentText(query.value(4).toString());
    ui->comboBoxDurationOfStudy->setCurrentText(query.value(7).toString());
    ui->comboBoxAcademicProgram->setCurrentText(query.value(5).toString());
    ui->comboBoxContractType->setCurrentText(query.value(6).toString());*/
}
